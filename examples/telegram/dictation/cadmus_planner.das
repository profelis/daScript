module cadmus_planner public

options gen2

require daslib/defer
require daslib/json_boost
require strings
require daslib/strings_boost

struct CadmusRetrievalPlan {
    @rename = "action"
    Action : string
    @optional
    @rename = "query"
    Query : string
    @optional
    @rename = "queries"
    Queries : array<string>
    @optional
    @rename = "sender"
    Sender : string
    @rename = "answer_language"
    AnswerLanguage : string
    @optional
    @rename = "limit"
    Limit : int
    @optional
    @rename = "message_id"
    MessageId : int64
    @optional
    @rename = "before"
    Before : int = 5
    @optional
    @rename = "after"
    After : int = 5
    @optional
    @rename = "before_message_id"
    BeforeMessageId : int64
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

def private append_cadmus_query(var queries : array<string>&; value : string) {
    let query = strip(value)
    if (empty(query) || length(queries) >= 6) {
        return
    }
    for (existing in queries) {
        if (existing == query) {
            return
        }
    }
    queries |> push_clone(query)
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
    delete plan.Queries
    plan.Action := action
    plan.Query := strip(js?["query"] ?? "")
    plan.Sender := strip(js?["sender"] ?? "")
    plan.AnswerLanguage := to_lower(strip(js?["answer_language"] ?? ""))
    plan.Limit = js?["limit"] ?? 0
    plan.MessageId = js?["message_id"] ?? 0l
    plan.Before = js?["before"] ?? 5
    plan.After = js?["after"] ?? 5
    plan.BeforeMessageId = js?["before_message_id"] ?? 0l
    let queries_json = js?["queries"]
    if (queries_json != null && queries_json.value is _array) {
        for (item in queries_json.value as _array) {
            if (item != null && item.value is _string) {
                append_cadmus_query(plan.Queries, item.value as _string)
            }
        }
    }
    append_cadmus_query(plan.Queries, plan.Query)
    if (empty(plan.Query) && !empty(plan.Queries)) {
        plan.Query := plan.Queries[0]
    }
    if ((action == "search_messages" || action == "message_timeline" || action == "search_web") &&
        empty(plan.Query)) {
        error = "planner action '{action}' requires a query"
        return false
    }
    if (length(plan.AnswerLanguage) != 2) {
        error = "planner requires a two-letter ISO answer_language"
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
    return sprint_json(plan, false)
}
