#include "headers/Client.h"

Client::Client() {
    this->keypair = new KeyPair;

}

Client::~Client() {
    delete this->keypair;
}