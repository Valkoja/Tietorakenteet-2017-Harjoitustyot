#pragma once

enum class Runway_activity {
    idle,
    landing,
    takeoff
};

enum class Error_code {
    success,
    fail,
    utility_range_error,
    underflow,
    overflow,
    fatal,
    not_present,
    duplicate_error,
    entry_inserted,
    entry_found,
    internal_error
};
