#include "StdAfx.h"
#include "argumentcheck.h"

// Our fixed array of valid schema names
const wchar_t* ArgumentCheck::s_schema_names[] = {
  GD_SCHEMA_TEXTFILE,
  GD_SCHEMA_IM,
  GD_SCHEMA_EMAIL,
  GD_SCHEMA_WEBPAGE,
  GD_SCHEMA_MEDIAFILE,
  GD_SCHEMA_FILE,
};

ArgumentCheck::ArgumentCheck() : uninstall_(false){
}

ArgumentCheck::~ArgumentCheck() {
}

bool ArgumentCheck::Check(int argc, TCHAR* argv[]) {
  ATLASSERT(argc >= 1);
  if (argc < 1)
    return false;

  ATLASSERT(schema_filters_.GetSize() == 0);

  // First arg is the name of the executable
  for (int i = 1; i < argc; i++) {
    ATLASSERT(argv[i] != NULL);
    if (argv[i][0] == _T('-') || argv[i][0] == _T('/')) {
      const TCHAR* arg = argv[i] + 1;

      switch (arg[0]) {
        // Check for uninstallation
        case _T('u'):
        case _T('U'):
          if (lstrcmpi(arg, _T("uninstall")) == 0) {
            uninstall_ = true;
            // no need for further parsing
            return true;
          } else {
            _tprintf(_T("Unknown argument: %s\n"), arg);
            return false;
          }
          break;

        // Check for the "schema" flag
        case _T('s'):
        case _T('S'):
          arg++;

          // unlikely, but just in case, lets jump over spaces
          while (_istspace(arg[0]))
            arg++;

          CComBSTR schema_name;
          if (FindMatchingSchema(CT2WEX<>(arg), &schema_name)) {
            _tprintf(_T("Will allow schema: %ls\n"), schema_name);
            ATLVERIFY(schema_filters_.Add(schema_name));
          } else {
            _tprintf(_T("Unable to find match for schema: %ls\n\n"), arg);
            PrintValidSchemaNames();
            return false;
          }
          break;
      }
    } else {
      _tprintf(_T("Unsupported option: %s\n"), argv[i][0]);
      return false;
    }
  }

  return true;
}

bool ArgumentCheck::FindMatchingSchema(const wchar_t* name, OUT BSTR* schema_name) {
  ATLASSERT(name != NULL);
  ATLASSERT(schema_name != NULL);

  int name_len = lstrlenW(name);

  for (int i = 0; i < sizeof(s_schema_names) / sizeof(s_schema_names[0]); ++i) {
    int schema_len = lstrlenW(s_schema_names[i]);
    if (name_len <= schema_len &&
        lstrcmpiW(s_schema_names[i] + schema_len - name_len, name) == 0) {
      *schema_name = ::SysAllocString(s_schema_names[i]);
      return true;
    }
  }

  return false;
}

void ArgumentCheck::PrintValidSchemaNames() {
  _tprintf(_T("Valid schema names:\n\n"));

  for (int i = 0; i < sizeof(s_schema_names) / sizeof(s_schema_names[0]); ++i) {
    _tprintf(_T("  %ls\n"), s_schema_names[i]);
  }

  _tprintf(_T("\nMatching partial schema names, is supported\n"));
}

void ArgumentCheck::PrintUsage() {
  _tprintf(_T("Google Desktop - Event Framework example\n\n")
           _T("Usage:\n\n")
           _T("To filter events by one or more schema names, use the -s switch.")
           _T("immediately following the -s switch, you specify either the full")
           _T("or partial name of the schema you want to filter by.\n\n")
           _T("E.g:\n")
           _T("  console_events -sEmail\n")
           _T("  console_events -sWebPage -sEmail\n")
           _T("  console_events _sGoogle.Desktop.TextFile -sGoogle.Desktop.IM\n")
           _T("  etc.\n\n")
           _T("To uninstall, use the 'uninstall' command:\n\n")
           _T("  console_events -uninstall\n\n")
           _T("Installation is done automatically when you first run the program\n\n"));
}

HRESULT ArgumentCheck::SetUserSpecifiedSchemaFilters(IGoogleDesktopEventSubscription* sub) {
  ATLASSERT(sub != NULL);

  HRESULT hr = S_OK;

  CComQIPtr<IGoogleDesktopSchemaFilter> schema_filter;

  for (int i = 0; i < schema_filters_.GetSize() && SUCCEEDED(hr); i++) {
    if (schema_filter == NULL) {
      CComPtr<IDispatch> disp;
      hr = sub->AddFilter(CComBSTR(GDEF_FILTER_SCHEMA), CComVariant(), &disp);
      ATLASSERT(SUCCEEDED(hr));
      if (FAILED(hr))
        break;

      schema_filter = disp;
    }

    ATLASSERT(schema_filter != NULL);

    hr = schema_filter->Allow(schema_filters_[i].m_T);
  }

  return hr;
}
