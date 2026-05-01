#include <chrono>
#include <functional>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "apresentacao_interfaces/msg/telemetria.hpp"

using namespace std::chrono_literals;

class SensorEmulator : public rclcpp::Node
{
public:
  SensorEmulator()
  : Node("sensor_emulator")
  {
    publisher_ = this->create_publisher<apresentacao_interfaces::msg::Telemetria>("telemetria", 10);
    timer_ = this->create_wall_timer(
      1s, std::bind(&SensorEmulator::publish, this));

   // Gerador de números aleatórios (normal/gaussiano)
   std::random_device rd;
   gen_ = std::mt19937(rd());
   dist_ = std::normal_distribution<float>(10.0, 1.0); // média=10, desvio=1
  }

private:
  void publish()
  {
    auto message = apresentacao_interfaces::msg::Telemetria();
    message.velocidade = dist_(gen_);
    RCLCPP_INFO(this->get_logger(), "Publicando: %.4f", message.velocidade);
    publisher_->publish(message);
  }

  std::mt19937 gen_;
  std::normal_distribution<float> dist_;

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<apresentacao_interfaces::msg::Telemetria>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SensorEmulator>());
  rclcpp::shutdown();
  return 0;
}
