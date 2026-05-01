#include <rclcpp/rclcpp.hpp>

class SensorReader : public rclcpp::Node {
    public:
    SensorReader() : Node("sensor_real") {

    }
    private:

    // implementar o sensor de verdade
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorReader>());
  rclcpp::shutdown();
  return 0;
}
