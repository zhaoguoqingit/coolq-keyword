#pragma once

#include <cqcppsdk/cqcppsdk.h>
#include <thread>
#include "appInf.h"
#pragma once
#define APPNAME "群关键词监控"

class mycq {
public:
public:
    //获取匿名信息
    static cq::User get_stranger_info(const int64_t user_id, const bool no_cache = false) {
        try {
            return cq::get_stranger_info(user_id, no_cache);
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }
        return cq::User();
    }

    //获取群列表 map
    static cq::Group get_group_info(const int64_t group_id, const bool no_cache = false) {
        try {
            return cq::get_group_info(group_id, no_cache);
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }

        return cq::Group();
    }

    //获取群列表 map
    static std::map<long long, cq::Group> get_group_list_map() {
        std::map<long long, cq::Group> groupList_map;
        auto groupList = get_group_list();
        for (auto group : groupList) {
            groupList_map[group.group_id] = group;
        }

        return groupList_map;
    }

    //获取群列表
    static std::vector<cq::Group> get_group_list() {
        try {
            return cq::get_group_list();
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }

        return {};
    }

    //获取群成员信息
    static cq::GroupMember get_group_member_info(const int64_t group_id, const int64_t user_id,
                                                 const bool no_cache = false) {
        try {
            return cq::get_group_member_info(group_id, user_id, no_cache);
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }

        return cq::GroupMember();
    }

    //异步发送群消息
    static void send_group_message_async(const int64_t group_id, const std::string &message, bool async = true) {
        if (async) {
            std::thread th(send_group_message, group_id, message);
            th.detach();
        } else {
            send_group_message(group_id, message);
        }
    }

    //发送群消息 正确返回 0  异常返回code
    static const int send_group_message(const int64_t group_id, const std::string &message) {
        try {
            cq::send_group_message(group_id, message);
            return 0;
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
            return e.code;
        }

        return -1;
    }

    //异步发送私聊消息
    static void send_private_message_async(const int64_t user_id, const std::string &message, bool async = true) {
        if (async) {
            std::thread th(send_private_message, user_id, message);
            th.detach();
        } else {
            send_private_message(user_id, message);
        }
    }

    //发送私聊消息  正确返回 0  异常返回code
    static const int send_private_message(const int64_t user_id, const std::string &message) {
        try {
            cq::send_private_message(user_id, message);
            return 0;
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
            return e.code;
        }

        return -1;
    }

    //踢出
    static void set_group_kick(const int64_t group_id, const int64_t user_id, const bool reject_future_request) {
        try {
            cq::set_group_kick(group_id, user_id, reject_future_request);
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }
    }

    //撤回消息
    static void delete_message(const int64_t message_id) {
        try {
            cq::delete_message(message_id);
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }
    }

    //禁言匿名
    static void set_group_anonymous_ban(const int64_t group_id, const cq::Anonymous &anonymous,
                                        const int64_t duration) {
        try {
            cq::set_group_anonymous_ban(group_id, anonymous, duration);
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }
    }

    //禁言
    static void set_group_ban(const int64_t group_id, const int64_t user_id, const int64_t duration) {
        try {
            cq::set_group_ban(group_id, user_id, duration);
        } catch (cq::ApiError &e) {
            cq::logging::info(APPNAME, e.what());
        }
    }
};
// namespace mycq