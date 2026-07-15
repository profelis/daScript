module cadmus_planner public

options gen2

require daslib/defer
require daslib/json_boost
require strings
require daslib/strings_boost

struct CadmusRetrievalPlan {
    Action : string
    Query : string
    Limit : int
    MessageId : int64
    Before : int = 5
    After : int = 5
    BeforeMessageId : int64
}

struct CadmusRetrievalArguments {
    @optional query : string
    @optional limit : int
    @optional message_id : int64
    @optional before : int
    @optional after : int
    @optional before_message_id : int64
}

def private cadmus_plan_json(response : string) : string {
    let clean = strip(replace(replace(response, "```json", ""), "```", ""))
    let first_brace = find(clean, '{')
    let last_brace = rfind(clean, "}")
    if (first_brace >= 0 && last_brace >= first_brace) {
        return slice(clean, first_brace, last_brace + 1)
    }
    return clean
}

def private is_cadmus_plan_action(action : string) : bool {
    return (action == "answer" || action == "search_messages" ||
            action == "message_timeline" || action == "get_message_context" ||
            action == "list_messages" || action == "search_web")
}

def parse_cadmus_retrieval_plan(
                                response : string;
                                var plan : CadmusRetrievalPlan&;
                                var error : string&
                                ) : bool {
    let object_text = cadmus_plan_json(response)
    if (empty(object_text)) {
        error = "planner response contains no JSON object"
        return false
    }
    var parse_error = ""
    var js = read_json(try_fixing_broken_json(object_text), parse_error)
    if (js == null) {
        error = "invalid planner JSON: {parse_error}"
        return false
    }
    defer() { unsafe { delete js } }
    let action = strip(js?["action"] ?? "")
    if (!is_cadmus_plan_action(action)) {
        error = "unknown planner action '{action}'"
        return false
    }
    plan = CadmusRetrievalPlan(
        Action = action,
        Query = strip(js?["query"] ?? ""),
        Limit = js?["limit"] ?? 0,
        MessageId = js?["message_id"] ?? 0l,
        Before = js?["before"] ?? 5,
        After = js?["after"] ?? 5,
        BeforeMessageId = js?["before_message_id"] ?? 0l)
    if ((action == "search_messages" || action == "message_timeline" || action == "search_web") &&
        empty(plan.Query)) {
        error = "planner action '{action}' requires a query"
        return false
    }
    if (action == "get_message_context" && plan.MessageId <= 0l) {
        error = "planner action 'get_message_context' requires a positive message_id"
        return false
    }
    error = ""
    return true
}

def cadmus_retrieval_arguments_json(plan : CadmusRetrievalPlan) : string {
    return sprint_json(CadmusRetrievalArguments(
        query = plan.Query,
        limit = plan.Limit,
        message_id = plan.MessageId,
        before = plan.Before,
        after = plan.After,
        before_message_id = plan.BeforeMessageId), false)
}
