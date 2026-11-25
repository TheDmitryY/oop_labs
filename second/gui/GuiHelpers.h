#ifndef GUI_HELPERS_H_
#define GUI_HELPERS_H_

#include <iostream>
#include <sstream>
#include <string>

namespace PersonnelGui {

/// Converts a managed UTF-16 System::String^ to a UTF-8 std::string.
inline std::string ToStdString(System::String^ managed) {
  if (System::String::IsNullOrEmpty(managed)) {
    return "";
  }
  array<System::Byte>^ bytes =
      System::Text::Encoding::UTF8->GetBytes(managed);
  if (bytes->Length == 0) {
    return "";
  }
  pin_ptr<System::Byte> pinned = &bytes[0];
  return std::string(reinterpret_cast<const char*>(pinned), bytes->Length);
}

/// Converts a UTF-8 std::string to a managed System::String^.
inline System::String^ FromStdString(const std::string& native) {
  if (native.empty()) {
    return System::String::Empty;
  }
  int length = static_cast<int>(native.size());
  array<System::Byte>^ bytes = gcnew array<System::Byte>(length);
  System::Runtime::InteropServices::Marshal::Copy(
      System::IntPtr(const_cast<char*>(native.data())), bytes, 0, length);
  return System::Text::Encoding::UTF8->GetString(bytes);
}

/// RAII helper that redirects std::cout into an internal std::ostringstream.
class CoutRedirector {
 public:
  CoutRedirector() : old_buf_(std::cout.rdbuf(buffer_.rdbuf())) {}
  ~CoutRedirector() { std::cout.rdbuf(old_buf_); }

  CoutRedirector(const CoutRedirector&) = delete;
  CoutRedirector& operator=(const CoutRedirector&) = delete;

  std::string GetOutput() const { return buffer_.str(); }

 private:
  std::ostringstream buffer_;
  std::streambuf* old_buf_;
};

}  // namespace PersonnelGui

#endif  // GUI_HELPERS_H_
