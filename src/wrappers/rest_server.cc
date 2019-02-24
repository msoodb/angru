#include "wrappers/rest_server.h"

#include <iostream>
#include <string>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include "tools/system.h"
#include "tools/security.h"
#include "controllers/entitie_controller.h"
#include "controllers/privilege_controller.h"
#include "controllers/security_role_controller.h"
#include "controllers/users_security_role_controller.h"
#include "controllers/mobile_operator_controller.h"
#include "controllers/aggrigator_controller.h"
#include "controllers/content_provider_controller.h"
#include "controllers/file_controller.h"
#include "controllers/avatar_controller.h"
#include "controllers/product_controller.h"
#include "controllers/product_document_controller.h"
#include "controllers/user_controller.h"
#include "controllers/service_controller.h"
#include "controllers/member_controller.h"
#include "controllers/subscription_controller.h"
#include "controllers/playlist_controller.h"
#include "controllers/channel_controller.h"
#include "controllers/publisher_controller.h"
#include "controllers/users_content_provider_controller.h"
#include "controllers/users_publisher_controller.h"

namespace angru{
namespace wrapper{

void RestServer::Setup(int port_number, int thread_count){
  Pistache::Port port(port_number);
  Pistache::Address addr(Pistache::Ipv4::any(), port);
  std::cout << "Using " <<  std::thread::hardware_concurrency() <<
    " Cores" << std::endl;
  std::cout << "Using " << port_number << " port number" << std::endl;
  std::cout << "Using " << thread_count << " threads" << std::endl;
  RestServer rest_server(addr);
  rest_server.Init(thread_count);
  rest_server.Start();
  rest_server.Shutdown();
}


RestServer::RestServer(Pistache::Address addr) :
  httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr)){
}

void RestServer::SetupRoutes() {
  using namespace angru::mvc::controller;
  using namespace Pistache::Rest::Routes;
  Options(router, "/*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/:", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:*/*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:*/*/:*", bind(&angru::security::authorization::doGetOptions));

  Post(router, "/login", bind(&UserController::doLogin));

  Get(router, "/files/:id", bind(&FileController::doGetFile));
  Post(router, "/files", bind(&FileController::doAddFile));

  Get(router, "/mobile_operators", bind(&MobileOperatorController::doGetMobileOperators));
	Get(router, "/mobile_operators/:id", bind(&MobileOperatorController::doGetMobileOperator));
	Delete(router, "/mobile_operators/:id", bind(&MobileOperatorController::doDeleteMobileOperator));
  Post(router, "/mobile_operators", bind(&MobileOperatorController::doAddMobileOperator));
	Put(router, "/mobile_operators/:id", bind(&MobileOperatorController::doUpdateMobileOperator));

  Get(router, "/aggrigators", bind(&AggrigatorController::doGetAggrigators));
  Get(router, "/aggrigators/:id", bind(&AggrigatorController::doGetAggrigator));
  Delete(router, "/aggrigators/:id", bind(&AggrigatorController::doDeleteAggrigator));
  Post(router, "/aggrigators", bind(&AggrigatorController::doAddAggrigator));
  Put(router, "/aggrigators/:id", bind(&AggrigatorController::doUpdateAggrigator));

  Get(router, "/content_providers", bind(&ContentProviderController::doGetContentProviders));
	Get(router, "/content_providers/:id", bind(&ContentProviderController::doGetContentProvider));
	Delete(router, "/content_providers/:id", bind(&ContentProviderController::doDeleteContentProvider));
  Post(router, "/content_providers", bind(&ContentProviderController::doAddContentProvider));
	Put(router, "/content_providers/:id", bind(&ContentProviderController::doUpdateContentProvider));

  Get(router, "/services", bind(&ServiceController::doGetServices));
  Get(router, "/services/:id", bind(&ServiceController::doGetService));
  Delete(router, "/services/:id", bind(&ServiceController::doDeleteService));
  Post(router, "/services", bind(&ServiceController::doAddService));
  Put(router, "/services/:id", bind(&ServiceController::doUpdateService));

  Get(router, "/products", bind(&ProductController::doGetProducts));
  Get(router, "/products/:id", bind(&ProductController::doGetProduct));
  Delete(router, "/products/:id", bind(&ProductController::doDeleteProduct));
  Post(router, "/products", bind(&ProductController::doAddProduct));
  Put(router, "/products/:id", bind(&ProductController::doUpdateProduct));

  Get(router, "/products/:product_id/documents", bind(&ProductDocumentController::doGetProductDocuments));
  Get(router, "/products/:product_id/documents/:id", bind(&ProductDocumentController::doGetProductDocument));
  Delete(router, "/products/:product_id/documents/:id", bind(&ProductDocumentController::doDeleteProductDocument));
  Post(router, "/products/:product_id/documents", bind(&ProductDocumentController::doAddProductDocument));
  Put(router, "/products/:product_id/documents/:id", bind(&ProductDocumentController::doUpdateProductDocument));

  Get(router, "/users", bind(&UserController::doGetUsers));
  Get(router, "/users/:id", bind(&UserController::doGetUser));
  Delete(router, "/users/:id", bind(&UserController::doDeleteUser));
  Post(router, "/users", bind(&UserController::doAddUser));
  Put(router, "/users/:id", bind(&UserController::doUpdateUser));
  Put(router, "/users/:id/password", bind(&UserController::doChangePassword));
  Post(router, "/users/:id/avatars", bind(&AvatarController::doAddAvatar));
  Get(router, "/users/:id/avatars", bind(&AvatarController::doGetAvatar));

	Get(router, "/entities", bind(&EntitieController::doGetEntities));
	Get(router, "/entities/:id", bind(&EntitieController::doGetEntitie));
	// Delete(router, "/entities/:id", bind(&EntitieController::doDeleteEntitie));
  // Post(router, "/entities", bind(&EntitieController::doAddEntitie));
	// Put(router, "/entities/:id", bind(&EntitieController::doUpdateEntitie));

  Get(router, "/privileges", bind(&PrivilegeController::doGetPrivileges));
	Get(router, "/privileges/:id", bind(&PrivilegeController::doGetPrivilege));
	Delete(router, "/privileges/:id", bind(&PrivilegeController::doDeletePrivilege));
  Post(router, "/privileges", bind(&PrivilegeController::doAddPrivilege));
	Put(router, "/privileges/:id", bind(&PrivilegeController::doUpdatePrivilege));

  Get(router, "/security_roles", bind(&SecurityRoleController::doGetSecurityRoles));
	Get(router, "/security_roles/:id", bind(&SecurityRoleController::doGetSecurityRole));
	Delete(router, "/security_roles/:id", bind(&SecurityRoleController::doDeleteSecurityRole));
  Post(router, "/security_roles", bind(&SecurityRoleController::doAddSecurityRole));
	Put(router, "/security_roles/:id", bind(&SecurityRoleController::doUpdateSecurityRole));

  Get(router, "/users_security_roles", bind(&UsersSecurityRoleController::doGetUsersSecurityRoles));
	Get(router, "/users_security_roles/:id", bind(&UsersSecurityRoleController::doGetUsersSecurityRole));
	Delete(router, "/users_security_roles/:id", bind(&UsersSecurityRoleController::doDeleteUsersSecurityRole));
  Post(router, "/users_security_roles", bind(&UsersSecurityRoleController::doAddUsersSecurityRole));
	Put(router, "/users_security_roles/:id", bind(&UsersSecurityRoleController::doUpdateUsersSecurityRole));

  Get(router, "/subscriptions", bind(&SubscriptionController::doGetSubscriptions));
  Get(router, "/subscriptions/:id", bind(&SubscriptionController::doGetSubscription));
  Delete(router, "/subscriptions/:id", bind(&SubscriptionController::doDeleteSubscription));
  Post(router, "/subscriptions", bind(&SubscriptionController::doAddSubscription));
  Put(router, "/subscriptions/:id", bind(&SubscriptionController::doUpdateSubscription));

  Get(router, "/members", bind(&MemberController::doGetMembers));
  Get(router, "/members/:id", bind(&MemberController::doGetMember));
  Delete(router, "/members/:id", bind(&MemberController::doDeleteMember));
  Post(router, "/members", bind(&MemberController::doAddMember));
  Put(router, "/members/:id", bind(&MemberController::doUpdateMember));

  Get(router, "/channels", bind(&ChannelController::doGetChannels));
	Get(router, "/channels/:id", bind(&ChannelController::doGetChannel));
	Delete(router, "/channels/:id", bind(&ChannelController::doDeleteChannel));
  Post(router, "/channels", bind(&ChannelController::doAddChannel));
	Put(router, "/channels/:id", bind(&ChannelController::doUpdateChannel));

  Get(router, "/playlists", bind(&PlaylistController::doGetPlaylists));
	Get(router, "/playlists/:id", bind(&PlaylistController::doGetPlaylist));
	Delete(router, "/playlists/:id", bind(&PlaylistController::doDeletePlaylist));
  Post(router, "/playlists", bind(&PlaylistController::doAddPlaylist));
	Put(router, "/playlists/:id", bind(&PlaylistController::doUpdatePlaylist));

  Get(router, "/publishers", bind(&PublisherController::doGetPublishers));
  Get(router, "/publishers/:id", bind(&PublisherController::doGetPublisher));
  Delete(router, "/publishers/:id", bind(&PublisherController::doDeletePublisher));
  Post(router, "/publishers", bind(&PublisherController::doAddPublisher));
  Put(router, "/publishers/:id", bind(&PublisherController::doUpdatePublisher));

  Get(router, "/users_content_providers", bind(&UsersContentProviderController::doGetUsersContentProviders));
  Get(router, "/users_content_providers/:id", bind(&UsersContentProviderController::doGetUsersContentProvider));
  Delete(router, "/users_content_providers/:id", bind(&UsersContentProviderController::doDeleteUsersContentProvider));
  Post(router, "/users_content_providers", bind(&UsersContentProviderController::doAddUsersContentProvider));
  Put(router, "/users_content_providers/:id", bind(&UsersContentProviderController::doUpdateUsersContentProvider));

  Get(router, "/users_publishers", bind(&UsersPublisherController::doGetUsersPublishers));
  Get(router, "/users_publishers/:id", bind(&UsersPublisherController::doGetUsersPublisher));
  Delete(router, "/users_publishers/:id", bind(&UsersPublisherController::doDeleteUsersPublisher));
  Post(router, "/users_publishers", bind(&UsersPublisherController::doAddUsersPublisher));
  Put(router, "/users_publishers/:id", bind(&UsersPublisherController::doUpdateUsersPublisher));
}

void RestServer::PrintCookies(const Pistache::Http::Request& req) {
    auto cookies = req.cookies();
    std::cout << "Cookies: [" << std::endl;
    const std::string indent(4, ' ');
    for (const auto& c: cookies) {
        std::cout << indent << c.name << " = " << c.value << std::endl;
    }
    std::cout << "]" << std::endl;
}

void RestServer::HandleReady(const Pistache::Rest::Request&,
  Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, "1");
}

void RestServer::Init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options()
        .threads(thr)
        .flags(Pistache::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    SetupRoutes();
}

void RestServer::Start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void RestServer::Shutdown() {
    httpEndpoint->shutdown();
}

} // wrapper
} // angru
