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

typedef map<string, string> Event;

class User{
    public:
        int id;
        string handle;
        User(){};
        User(int id, string handle): id(id), handle(handle){};
};

bool operator==(const User& first, const User& second){
    return first.id == second.id && first.handle == second.handle;
};

class DataStore{
    public:
        list<User> users;
};

auto createUserEventToUser = [](Event event){
    return User(stoi(event["id"]), event["handle"]);
};

auto filterEventByEventType = [](Event event, const auto& eventType){ 
    return event["type"] == eventType;
};

template<typename Entity>
auto playEvents = [](const auto& events, const auto& eventType, auto playEvent){
    list<Event> allEventsOfType;
    auto filterEventByThisEventType = bind(filterEventByEventType, _1, eventType);
    copy_if(events.begin(), events.end(), back_insert_iterator(allEventsOfType), filterEventByThisEventType);
    list<Entity> entities(allEventsOfType.size());
    transform(allEventsOfType.begin(), allEventsOfType.end(), entities.begin(), playEvent); 
    return entities;
};

class EventStore : public list<Event>{
    public:
        EventStore() : list<Event>(){
        };

        DataStore play(){
            DataStore dataStore;
            dataStore.users = playEvents<User>(*this, "CreateUser", createUserEventToUser);
            return dataStore;
        };
};

auto makeCreateUserEvent = [](const string& handle, const int id){
    return Event{
        {"type", "CreateUser"}, 
            {"handle", handle}, 
            {"id", to_string(id)}
    };
};

int id = 1;
auto createUser = [](string handle, EventStore& eventStore){
    eventStore.push_back(makeCreateUserEvent(handle, id));
    return id;
};

auto makePostMessageEvent = [](const int userId, const string& message, int id){
    return Event{
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

TEST_CASE("Run events and get the user store"){
    auto handle = "alexboly";
    EventStore eventStore;

    auto alexId = createUser(handle, eventStore);
    auto dataStore = eventStore.play();

    CHECK_EQ(dataStore.users.back(), User(alexId, handle));
}
