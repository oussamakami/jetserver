<?php
ignore_user_abort(true); // Ignore user aborts
set_time_limit(0); // Set no time limit for execution

// Output headers to indicate that this is a CGI script
header("Content-type: text/plain");
header("Cache-Control: no-cache"); // Prevent caching


while (true) {}
?>
