/**
 * @file udp_repeater.cc
 * @brief Main file for the udp repeater
 */
#include <gflags/gflags.h>
#include <string>

#include "udp_client.h"
#include "udp_server.h"

DEFINE_uint64(rx_port_id, 8080, "");
DEFINE_uint64(tx_port_id, 8081, "");


int main(int argc, char* argv[]) {
  int ret = EXIT_FAILURE;

  gflags::SetUsageMessage("rx_port_id, tx_port_id");
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::string cur_directory = __STRING(PROJECT_DIRECTORY);
  
  unsigned tx_port = FLAGS_tx_port_id;
  unsigned rx_port = FLAGS_rx_port_id;
  
  std::printf("Tx port: %d, rx port :%d\n", tx_port, rx_port);
  ret = EXIT_SUCCESS;
  std::printf("Udp Repeater application terminated!\n");
  gflags::ShutDownCommandLineFlags();
  return ret;
}
