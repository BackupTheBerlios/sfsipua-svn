#pragma once

class ArgumentCheck {
public:
  ArgumentCheck();
  ~ArgumentCheck();

  /**
  * Loops through the arguments and checks for those we support.
  *
  * We support the 'uninstall' command:
  *
  *   console_events -uninstall
  *
  * Currently only the [s]chema flag is supported.  The schema flag
  * must be followed by a valid schema name or a partial schema name.
  *
  * E.g:
  *   console_events -sEmail
  *   console_events -sWebPage -sEmail
  *   console_events _sGoogle.Desktop.TextFile -sGoogle.Desktop.IM
  *   etc.
  */
  bool Check(int argc, TCHAR* argv[]);

  ///@returns true if the user wants to uninstall
  inline bool IsUninstall() { return uninstall_; }

  /// Outputs the names of valid schemas
  void PrintValidSchemaNames();

  /// Prints basic usage information
  void PrintUsage();

  /**
  * We allow the user to filter the events we receive by schema.
  * This function configures an existing subscription object
  * so that only events that match certain schema(s) will be
  * delivered to us.  The names of the schemas are passed
  * to us via input arguments, parsed by the @ref Check routine.
  */
  HRESULT SetUserSpecifiedSchemaFilters(IGoogleDesktopEventSubscription* sub);

protected:
  /// Matches a partial schema name to a complete one
  bool FindMatchingSchema(const wchar_t* name, OUT BSTR* schema_name);

protected:
  bool uninstall_;
  CSimpleArray<CAdapt<CComBSTR> > schema_filters_;

  static const wchar_t* s_schema_names[];
};
