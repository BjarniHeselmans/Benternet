#include <string>
#include <iostream>
#include <random>
#include <zmq.hpp>

int main() {
    zmq::context_t context(1);

    // SUB socket luistert naar requests
    zmq::socket_t sub_socket(context, zmq::socket_type::sub);
    sub_socket.connect("tcp://benternet.pxl-ea-ict.be:24042");

    // PUSH socket stuurt antwoorden
    zmq::socket_t push_socket(context, zmq::socket_type::push);
    push_socket.connect("tcp://benternet.pxl-ea-ict.be:24041");

    // Subscribe op alle dobbelsteen aanvragen
    std::string sub_topic = "BjarniDobbelsteen?>";
    sub_socket.setsockopt(ZMQ_SUBSCRIBE, sub_topic.c_str(), sub_topic.length());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 6);

    std::cout << "Bjarni's Service is actief..." << std::endl;

    while (true) {
        zmq::message_t request;
        sub_socket.recv(request, zmq::recv_flags::none);

        std::string received_msg = request.to_string();
        std::cout << "Ontvangen verzoek: " << received_msg << std::endl;

        // Haal username uit bericht
        std::string user = received_msg.substr(sub_topic.length());

        // Doe een dobbelsteenworp
        int roll = distrib(gen);

        // Bouw het antwoordbericht volgens generieke structuur
        std::string response = "BjarniDobbelsteen!>" + user + std::to_string(roll);

        // Stuur het antwoord terug via PUSH
        zmq::message_t msg(response.size());
        memcpy(msg.data(), response.c_str(), response.size());

        push_socket.send(msg, zmq::send_flags::none);
        std::cout << "Antwoord verstuurd: " << response << std::endl;
    }

    return 0;
}
