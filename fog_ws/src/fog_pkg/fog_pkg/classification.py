import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from sensor_msgs.msg import CompressedImage
from std_msgs.msg import Int32MultiArray
from cv_bridge import CvBridge
import cv2
from ultralytics import YOLO
import threading
import asyncio
import numpy as np


class ClassificationNode(Node):
    def __init__(self):
        super().__init__('classification_node')
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
        self.model = YOLO("v10_final.pt")
        self.classNames = ['Derecha-pannels', 'Izquierda-pannels', 'Jaune-sema', 'Prio-pannels', 
                           'Red-sema', 'Rondpoint-pannels', 'Stop-pannels', 'Toutdroit-pannels', 
                           'Travaux-pannels', 'Vert-sema']
        self.get_logger().info('YOLO Node has started')
        self.image_processing_thread = threading.Thread(target=self.process_images)
        self.latest_image = None
        self.lock = threading.Lock()
        self.image_processing_thread.start()

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
        with self.lock:
            self.latest_image = cv_image

    def handle_image(self, cv_image):
        try:
            results = self.model(cv_image, stream=True)
            result_index = [int(box.cls) for r in results for box in r.boxes if int(box.cls) < len(self.classNames)]
            self.publish_signals(result_index)
        except Exception as e:
            self.get_logger().error(f'Error processing image: {str(e)}')

    def publish_signals(self, results):
        msg = Int32MultiArray()
        msg.data = results
        self.publisher.publish(msg)

class ClassificationNodeSimple(Node):
    def __init__(self):
        super().__init__('classification_node')
        self.subscription = self.create_subscription(
            Image,
            '/camera/image_raw',
            self.image_callback,
            10)
        self.publisher = self.create_publisher(Int32MultiArray, 'classification_results', 10)
        self.bridge = CvBridge()
        self.model = YOLO("best(8).pt")
        self.classNames = ['Derecha-pannels', 'Izquierda-pannels', 'Jaune-sema', 'Prio-pannels', 
                           'Red-sema', 'Rondpoint-pannels', 'Stop-pannels', 'Toutdroit-pannels', 
                           'Travaux-pannels', 'Vert-sema']
        self.get_logger().info('YOLO Node has started')

    async def image_callback(self, msg):
        thread = threading.Thread(target=self.handle_image, args=(msg,))
        thread.start()

    def handle_image(self, msg):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
            results = self.model(cv_image, stream=True)

            result_index = []  

            for r in results:
                boxes = r.boxes
                for box in boxes:
                    cls = int(box.cls)
                    result_index.append(cls)
                    if cls < len(self.classNames):
                        self.get_logger().info(f"Class name --> {self.classNames[cls]}")
                    else:
                        self.get_logger().info("Class name --> Unknown")

            self.publish_signals(result_index)
        except Exception as e:
            self.get_logger().error(f'Error processing image: {str(e)}')

    def publish_signals(self, results):
        msg = Int32MultiArray()
        msg.data = results
        self.publisher.publish(msg)
        self.get_logger().info(f'Published signals: {results}')

def main(args=None):
    rclpy.init(args=args)
    node = ClassificationNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

