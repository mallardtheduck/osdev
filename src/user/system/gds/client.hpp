#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <set>
#include <memory>
#include <map>
#include <btos/bt_msg.h>
#include <btos/imessagehandler.hpp>
#include "surface.hpp"

extern const size_t MaxSurfaceSize;
extern std::map<uint64_t, std::weak_ptr<Surface>> allSurfaces;

namespace btos_api{
	class Message;
}

class Client : public btos_api::IMessageHandler{
private:
	btos_api::bt_pid_t pid;
	std::set<std::shared_ptr<Surface>> surfaces;
	std::shared_ptr<Surface> currentSurface;
	
	gds_TextParameters txtParams;
public:
	Client(btos_api::bt_pid_t pid);
	~Client();
	
	bool HandleMessage(const btos_api::Message &msg) override;
};

void Service(btos_api::bt_pid_t root_pid);

#endif // CLIENT_HPP
