@rem run normally (no filtering)
debug\console_events 

@rem Only allow web events
debug\console_events -sWebPage

@rem Only allow text files and email
debug\console_events -sTextFile -sEmail

@rem uninstall
debug\console_events -uninstall