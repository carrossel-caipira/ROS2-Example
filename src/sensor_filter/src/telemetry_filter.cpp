#include "rclcpp/rclcpp.hpp"
#include "apresentacao_interfaces/msg/telemetria.hpp"

class TelemetryFilter : public rclcpp::Node
{
public:
  TelemetryFilter()
  : Node("telemetry_filter")
  {
    subscription_ = this->create_subscription<apresentacao_interfaces::msg::Telemetria>(
      "telemetria", 10,
      std::bind(&TelemetryFilter::telemetry_callback, this, std::placeholders::_1));
    
      this->declare_parameter<float>("max_deviation", 2.0);

      this->get_parameter("max_deviation", desvioMaximo_);
  }

private:
  void telemetry_callback(const apresentacao_interfaces::msg::Telemetria & msg)
  {
    RCLCPP_INFO(this->get_logger(), "Recebi: %.4f", msg.velocidade);
    buffer_.push_back(msg.velocidade);

    if (buffer_.size() > 10)
        buffer_.erase(buffer_.begin());

    float media = std::accumulate(buffer_.begin(), buffer_.end(), 0.0f) / buffer_.size();

    float diff = std::abs(msg.velocidade - media);

    if (diff > desvioMaximo_)
        RCLCPP_INFO(this->get_logger(), "Leitura invalido encontrado: %.4f", msg.velocidade);

    // continuar fluxo de dados...
  }

  std::vector<float> buffer_;
  float desvioMaximo_;

  rclcpp::Subscription<apresentacao_interfaces::msg::Telemetria>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TelemetryFilter>());
  rclcpp::shutdown();
  return 0;
}
