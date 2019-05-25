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

auto makeNext = [](auto value, auto lambda){
    return make_pair(value, lambda);
};

auto value = [](auto previous){
    return previous.first;
};

auto lambda = [](auto previous){
    return previous.second;
};

auto initNextId = [](int initialId){
    function<int(int)> nextId = [](int lastId){
        return lastId + 1;
    };

    return makeNext(initialId, nextId);
};

auto getNextId = [](pair<int, function<int(int)>> previous){
    auto previousId = value(previous);
    auto functionToApply = lambda(previous);
    int newValue = functionToApply(previousId);
    return makeNext(newValue, functionToApply);
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

auto makePostMessageEvent = [](const int userId, const string& message, int id){
    return map<string, string>{
            {"type", "PostMessage"}, 
            {"userId", to_string(userId)}, 
            {"message", message},
            {"id", to_string(id)}
    };
};

auto postMessage = [](const int userId, const string& message, EventStore& eventStore){
    eventStore.push_back(makePostMessageEvent(userId, message, id));
    return id;
};

TEST_CASE("Id"){
    auto idGenerator = initNextId(1);

    CHECK_EQ(1, value(idGenerator)); 

    idGenerator = getNextId(idGenerator);
    CHECK_EQ(2, value(idGenerator)); 
}

TEST_CASE("Create User"){
    auto handle = "alexboly";
    EventStore eventStore;

    auto alexId = createUser(handle, eventStore);

    auto expectedEvent = makeCreateUserEvent(handle, alexId);
    auto event = eventStore.back();
    CHECK_EQ(event, expectedEvent);
}

TEST_CASE("Post Message"){
    auto handle = "alexboly";
    auto message = "Hello, world!";
    EventStore eventStore;

    auto alexId = createUser(handle, eventStore);
    auto messageId = postMessage(alexId, message, eventStore);

    auto expectedEvent = makePostMessageEvent(alexId, message, messageId);
    auto event = eventStore.back();
    CHECK_EQ(event, expectedEvent);
}

//    createUser("johndoe", eventStore);
//    postMessage(alexId, "Hello, world!");
//    postMessage(johnId, "Hi @alexboly");
//    auto messageId = postMessage(alexId, "Hi @johndoe");
//    likeMessage(johnId, messageId);
