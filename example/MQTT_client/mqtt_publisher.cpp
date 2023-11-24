// Title: MQTT Publisher
// This code has not debug yet.

#include <iostream>
#include <string>
#include "mqtt/client.h"

typedef String      std::string;
typedef Address     String;
typedef UID         String;
typedef Client      mqtt::client;
typedef ConnectOpts mqtt::connect_options;
typedef Message     mqtt::message_ptr;

using std::cout;
using std::endl;
using mqtt::message::create;

const Address url = "tcp://127.0.0.1:1883";
const UID clientId = "";

int main() {
  cout << "Start connecting to broker " << url << "...";
  Client client{url, clientId};
  ConnectOpts opts;
  opts.set_clean_session(true);
  opts.set_automatic_reconnect(10, 30);
  opts.set_keep_alive_interval(30);

  client.connect(opts);
  if (!client.is_connected()) {
    cout << "Failed." << endl;
    return 1;
  }
  cout << "completed" << endl;

  cout << "Sending message...";
  Message msg{create(topic, payload)};
  client.publish(msg);
  cout << "completed" << endl;

  cout << "Disconnect from broker..." << endl;
  client.disconnect();
  return 0;
}
