module cadmus_rules public

options gen2

require strings
require daslib/strings_boost
require daslib/strings_convert

def is_cadmus_command(text, name : string) : bool {
    let lower = to_lower(strip(text))
    let tokens <- split_by_chars(lower, " \t\r\n")
    if (empty(tokens)) {
        return false
    }
    let command = tokens[0]
    return command == "/{name}" || starts_with(command, "/{name}@")
}

def is_cadmus_command_for_bot(text, name, bot_username : string) : bool {
    let lower = to_lower(strip(text))
    let tokens <- split_by_chars(lower, " \t\r\n")
    if (empty(tokens)) {
        return false
    }
    let command = tokens[0]
    if (command == "/{name}") {
        return true
    }
    let target = to_lower(strip(trim_prefix(bot_username, "@")))
    return !empty(target) && command == "/{name}@{target}"
}

def private has_alias_boundary(text, alias : string) : bool {
    return (text == alias || starts_with(text, "{alias} ") || starts_with(text, "{alias}\t") ||
            starts_with(text, "{alias}\r") || starts_with(text, "{alias}\n") || starts_with(text, "{alias},") ||
            starts_with(text, "{alias}:") || starts_with(text, "{alias}!") || starts_with(text, "{alias}?"))
}

def starts_with_cadmus_alias(text, aliases_csv : string) : bool {
    let original = strip(text)
    let lower = to_lower(strip(text))
    let aliases <- split(aliases_csv, ",")
    for (alias in aliases) {
        let exact_alias = strip(alias)
        let lower_alias = to_lower(exact_alias)
        if (!empty(exact_alias) &&
            (has_alias_boundary(original, exact_alias) || has_alias_boundary(lower, lower_alias))) {
            return true
        }
    }
    return false
}

def quote_cadmus_history(text : string) : string {
    let json = sprint_json(text, false)
    return replace_multiple(json, [
        (text = "<", replacement = "\\u003c"),
        (text = ">", replacement = "\\u003e")])
}

def cadmus_rolling_24h(now : int64; var from_time, until_time : int64&) {
    from_time = now - 86400l
    until_time = now + 1l
}

def parse_cadmus_local_date(value : string; var from_time, until_time : int64&) : bool {
    let parts <- split(value, "-")
    if (length(parts) != 3) {
        return false
    }
    let year_r = try_to_int(parts[0])
    let month_r = try_to_int(parts[1])
    let day_r = try_to_int(parts[2])
    if (year_r |> is_err || month_r |> is_err || day_r |> is_err) {
        return false
    }
    let year = year_r |> unwrap
    let month = month_r |> unwrap
    let day = day_r |> unwrap
    if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false
    }
    from_time = int64(mktime(year, month, day, 0, 0, 0))
    until_time = int64(mktime(year, month, day + 1, 0, 0, 0))
    return format_time(mktime(year, month, day, 12, 0, 0), "%Y-%m-%d") == value
}
