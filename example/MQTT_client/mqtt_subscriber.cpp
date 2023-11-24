// Title: MQTT Subscriber
// This code has not debug yet.

#include <iostream>
#include <string>
#include "mqtt/client.h"

typedef String       std::string;
typedef Address      String;
typedef UID          String;
typedef Topic        String;
typedef Client       mqtt::client;
typedef ConnectOpts  mqtt::connect_options;
typedef ConstMessage mqtt::const_message_ptr;

using std::cout;
using std::endl;
using std::tolower;
using std::cin;

const Address url = "tcp://127.0.0.1:1883";
const UID clientId = "";
const Topic subscribeTopic[] = {

};

void onMessage(ConstMessage);

int main() {
  cout << "Start connecting to broker " << url << "...";
  Client client{url, clientId};

  client.set_message_callback(onMessage);
  for (Topic topic: subscribeTopic)
    client.subscribe(topic);

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
  
  while (tolower(cin.get()) != 'q');

  cout << "Disconnect from broker..." << endl;
  return 0;

}
