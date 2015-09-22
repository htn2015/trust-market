Overview
=========
The goal is to create a decentralized marketplace based on a web of trust. 

The trustworthiness of a node is computed using [a simple algebra of trust](http://folk.uio.no/josang/papers/Jos1999-NDSS.pdf).

To do
======

* Client program base
	* Generating key pair (RSA)
	* Storing data (SQLite)
	* Communication between clients (Sockets)
* Trust Algorithm
	* Scan network and build graph
	* Retrieve trustworthiness
	* Connect to vendors
	* Review transactions
	* Update weights
* Simulation demonstrating the evolution of the network
* GUI client
