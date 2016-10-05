/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cm_codecvt_hxx
#define cm_codecvt_hxx

#include <codecvt>
#include <vector>

class codecvt : public std::codecvt<char, char, mbstate_t>
{
public:
  enum Encoding
  {
    None,
    UTF8,
    ANSI
  };

#ifdef CMAKE_BUILD_WITH_CMAKE

  codecvt(Encoding encoding);

protected:
  virtual ~codecvt();
  virtual bool do_always_noconv() const throw();
  virtual result do_out(mbstate_t& state, const char* from,
                        const char* from_end, const char*& from_next, char* to,
                        char* to_end, char*& to_next) const;
  virtual result do_unshift(mbstate_t& state, char* to, char*,
                            char*& to_next) const;
  virtual int do_max_length() const throw();
  virtual int do_encoding() const throw();

private:
  typedef struct
  {
    bool used;
    unsigned char totalBytes;
    unsigned char bytesLeft;
    char bytes[4];
  } State;

  unsigned int findStateId() const;

  bool m_noconv;
  unsigned int m_codepage;
  mutable std::vector<State> m_states;
  mutable unsigned int m_lastState;

#endif
};

#endif
