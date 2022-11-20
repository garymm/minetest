/*
Minetest
Copyright (C) 2010-2013 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

#include "irrlichttypes_extrabloated.h"
#include "client/client.h"
#include <zmqpp/zmqpp.hpp>
#include <string>

class Recorder
{
public:
	Recorder(std::string zmq_port): sender(context, zmqpp::socket_type::publish) {
		try {
        	sender.bind(zmq_port);
		} catch (zmqpp::zmq_internal_exception &e) {
			errorstream << "ZeroMQ error: " << e.what() << " (port: " << zmq_port << ")" << std::endl;
			throw e;
		};
    };

    void sendDataOut(Client *client);

private:
    zmqpp::context context;
    zmqpp::socket sender;
};