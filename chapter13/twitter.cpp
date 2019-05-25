#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

class EventStore : public list<map<string, string>>{
    public:
        EventStore() : list<map<string, string>>(){
        };
};

int id = 1;

auto makeCreateUserEvent = [](const string& handle, const int id){
    return map<string, string>{
            {"type", "CreateUser"}, 
            {"handle", handle}, 
            {"id", to_string(id)}
    };
};

auto createUser = [](string handle, EventStore& eventStore){
    eventStore.push_back(makeCreateUserEvent(handle, id));
    return id;
};

TEST_CASE("Create User"){
    auto handle = "alexboly";
    EventStore eventStore;

    auto alexId = createUser(handle, eventStore);

    auto expectedEvent = makeCreateUserEvent(handle, alexId);
    auto event = eventStore.front();
    CHECK_EQ(event, expectedEvent);
}

//    createUser("johndoe", eventStore);
//    postMessage(alexId, "Hello, world!");
//    postMessage(johnId, "Hi @alexboly");
//    auto messageId = postMessage(alexId, "Hi @johndoe");
//    likeMessage(johnId, messageId);


