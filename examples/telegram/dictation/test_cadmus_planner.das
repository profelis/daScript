options gen2
options no_unused_function_arguments = false

require dastest/testing_boost
require cadmus_planner

[test]
def test_parse_cadmus_retrieval_plan(t : T?) {
    var plan = CadmusRetrievalPlan()
    var error = ""
    t |> success(parse_cadmus_retrieval_plan(
        "```json\n\{\"action\":\"search_messages\",\"query\":\"рыбалка\",\"limit\":8}\n```",
        plan, error), error)
    t |> equal(plan.Action, "search_messages")
    t |> equal(plan.Query, "рыбалка")
    t |> equal(plan.Limit, 8)

    error = ""
    t |> success(parse_cadmus_retrieval_plan(
        "Plan:\n\{\"action\":\"search_web\",\"query\":\"Brave pricing\"}\nDone.",
        plan, error), error)
    t |> equal(plan.Action, "search_web")
    t |> equal(plan.Query, "Brave pricing")

    error = ""
    t |> success(parse_cadmus_retrieval_plan("\{\"action\":\"answer\"}", plan, error), error)
    t |> equal(plan.Action, "answer")

    error = ""
    t |> success(parse_cadmus_retrieval_plan(
        "\{\"action\":\"get_message_context\",\"message_id\":42,\"before\":3,\"after\":7}",
        plan, error), error)
    t |> equal(plan.MessageId, 42l)
    t |> equal(plan.Before, 3)
    t |> equal(plan.After, 7)
    t |> equal(cadmus_retrieval_arguments_json(plan),
               "\{\"message_id\":42,\"before\":3,\"after\":7}")

    error = ""
    t |> success(!parse_cadmus_retrieval_plan(
        "\{\"action\":\"search_messages\",\"query\":\"\"}", plan, error))
    t |> success(!empty(error))

    error = ""
    t |> success(!parse_cadmus_retrieval_plan(
        "\{\"action\":\"invent_tool\",\"query\":\"x\"}", plan, error))
    t |> success(!empty(error))

    error = ""
    t |> success(!parse_cadmus_retrieval_plan("not json", plan, error))
    t |> success(!empty(error))
}
