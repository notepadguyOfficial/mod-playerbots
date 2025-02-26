/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it
 * and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_SAYACTION_H
#define _PLAYERBOT_SAYACTION_H

#include "Action.h"
#include "PlayerbotAI.h"
#include "NamedObjectContext.h"
#include "QuestAction.h"

class PlayerbotAI;
class SayAction : public Action, public Qualified
{
public:
    SayAction(PlayerbotAI* botAI);

    bool Execute(Event event) override;
    bool isUseful() override;
    std::string const getName() override { return "say::" + qualifier; }

private:
    static std::map<std::string, std::vector<std::string>> stringTable;
    static std::map<std::string, uint32> probabilityTable;
};

typedef std::pair<WorldPacket, uint32> delayedPacket;
typedef std::vector<delayedPacket> delayedPackets;
typedef std::future<delayedPackets> futurePackets;

class ChatReplyAction : public Action
{
public:
    ChatReplyAction(PlayerbotAI* ai) : Action(ai, "chat message") {}
    virtual bool Execute(Event event) { return true; }
    bool isUseful() { return true; }

    static void GetAIChatPlaceholders(std::map<std::string, std::string>& placeholders, Unit* sender = nullptr, Unit* receiver = nullptr);
    static void GetAIChatPlaceholders(std::map<std::string, std::string>& placeholders, Unit* unit, const std::string preFix = "bot", Player* observer = nullptr);
    static WorldPacket GetPacketTemplate(Opcodes op, uint32 type, Unit* sender, Unit* target = nullptr, std::string channelName = "");
    static delayedPackets LinesToPackets(const std::vector<std::string>& lines, WorldPacket packetTemplate, bool debug = false, uint32 MsPerChar = 0, WorldPacket emoteTemplate = WorldPacket());

    static delayedPackets GenerateResponsePackets(const std::string json, const WorldPacket chatTemplate, const WorldPacket emoteTemplate, const WorldPacket systemTemplate, const std::string startPattern, const std::string endPattern, const std::string deletePattern, const std::string splitPattern, bool debug = false);

    static void ChatReplyDo(Player* bot, uint32& type, uint32& guid1, uint32& guid2, std::string& msg, std::string& chanName, std::string& name);
    static bool HandleThunderfuryReply(Player* bot, ChatChannelSource chatChannelSource, std::string& msg, std::string& name);
    static bool HandleToxicLinksReply(Player* bot, ChatChannelSource chatChannelSource, std::string& msg, std::string& name);
    static bool HandleWTBItemsReply(Player* bot, ChatChannelSource chatChannelSource, std::string& msg, std::string& name);
    static bool HandleLFGQuestsReply(Player* bot, ChatChannelSource chatChannelSource, std::string& msg, std::string& name);
    static bool SendGeneralResponse(Player* bot, ChatChannelSource chatChannelSource, std::string& responseMessage, std::string& name);
    static std::string GenerateReplyMessage(Player* bot, std::string& incomingMessage, uint32& guid1, std::string& name);
};
#endif
