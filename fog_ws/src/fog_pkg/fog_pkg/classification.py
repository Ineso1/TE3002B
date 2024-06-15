import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from std_msgs.msg import Int32MultiArray
import cv2
from ultralytics import YOLO
import asyncio
import threading
import numpy as np

# LAST MODEL :)
model_v11 = True

# VISUALIZATION
cam_view = False

class ClassificationNode(Node):
    def __init__(self):
        super().__init__('classification_node')
        self.confidence = 0.60
        qos_policy = rclpy.qos.QoSProfile(
            depth=1,
            reliability=rclpy.qos.QoSReliabilityPolicy.RELIABLE,
            durability=rclpy.qos.QoSDurabilityPolicy.VOLATILE)
        self.subscription = self.create_subscription(
            CompressedImage,
            '/camera/image_compressed',
            self.image_callback,
            qos_policy)
        self.publisher = self.create_publisher(Int32MultiArray, 'classification_results', 10)
        
        if(!model_v11):
            self.model = YOLO("best(8).pt")
        else:
            self.model = YOLO("model_v11.pt")
        
        if !model_v11 :
            self.classNames = ['Derecha-pannels', 'Izquierda-pannels', 'Jaune-sema', 'Prio-pannels', 
                            'Red-sema', 'Rondpoint-pannels', 'Stop-pannels', 'Toutdroit-pannels', 
                            'Travaux-pannels', 'Vert-sema']
                           
        self.classNames = ['Construction', 'Forward', 'Give_way', 'Green', 'Left', 
                                    'Red', 'Right', 'Roundabout', 'Stop', 'Yellow']
        
        self.color = [
            (65, 105, 225),  # Derecha-pannels      # Construction
            (255, 140, 0),   # Izquierda-pannels    # Forward
            (255, 215, 0),   # Jaune-sema           # Give-way
            (255, 20, 147),  # Prio-pannels         # Green
            (220, 20, 60),   # Red-sema             # Left
            (0, 128, 128),   # Rondpoint-pannels    # Red
            (139, 0, 0),     # Stop-pannels         # Right
            (34, 139, 34),   # Toutdroit-pannels    # Roundabout
            (160, 82, 45),   # Travaux-pannels      # Stop
            (50, 205, 50)    # Vert-sema            # Yellow
        ]

        self.get_logger().info('YOLO Node has started')
        self.image_processing_thread = threading.Thread(target=self.process_images)
        self.latest_image = None
        self.lock = threading.Lock()
        self.image_processing_thread.start()

    def visualize_preds(self, detection_metadata):
        cls, bbox, frame = detection_metadata
        local_frame = frame.copy()
        detections = zip(cls, bbox)
        for (cls, bbox) in detections:
            cls = int(cls)
            bbox = bbox.astype(int)

            point1 = ((int(bbox[0]-bbox[2]/2), 
                       int(bbox[1]-bbox[3]/2)))
            
            point2 = ((int(bbox[0]+bbox[2]/2), 
                       int(bbox[1]+bbox[3]/2)))
            
            cls_id = self.classNames[cls]
            color = self.color[cls]
            
            cv2.rectangle(local_frame, point1, point2, color, 3)
            cv2.putText(local_frame, cls_id, (bbox[0], bbox[1]), 
                        cv2.FONT_HERSHEY_COMPLEX, 0.5, color)
            
        cv2.imshow('Traffic Detector', local_frame)
        cv2.waitKey(1)

    def process_images(self):
        while rclpy.ok():
            if self.latest_image is not None:
                with self.lock:
                    image_to_process = self.latest_image
                    self.latest_image = None
                self.handle_image(image_to_process)

    def image_callback(self, msg):
        np_arr = np.frombuffer(msg.data, np.uint8)
        cv_image = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
        cv_image = cv2.flip(cv_image, 0)
        cv_image = cv2.flip(cv_image, 1)

        with self.lock:
            self.latest_image = cv_image

    def handle_image(self, cv_image):
        try:
            results = self.model.predict(cv_image, conf = self.confidence)
            result_index = [int(box.cls) for r in results for box in r.boxes if int(box.cls) < len(self.classNames)]
            #
            if cam_view:
                if len(results) > 0:
                    results = results[0]
                    cls = results.boxes.cls.numpy()
                    bbox = results.boxes.xywh.numpy()
                    self.visualize_preds((cls, bbox, cv_image))

            self.publish_signals(result_index)
        except Exception as e:
            self.get_logger().error(f'Error processing image: {str(e)}')

    def publish_signals(self, results):
        msg = Int32MultiArray()
        msg.data = results
        self.publisher.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = ClassificationNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

