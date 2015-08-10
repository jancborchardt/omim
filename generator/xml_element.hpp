#pragma once

#include "base/math.hpp"


#include "std/string.hpp"
#include "std/vector.hpp"
#include "std/map.hpp"

#include "std/iostream.hpp"
#include "std/exception.hpp"
#include "std/iomanip.hpp"

struct XMLElement
{
  enum ETag
  {
    ET_UNKNOWN = 0,
    ET_OSM = 0x736F, // "os"
    ET_NODE = 0x6F6E, // "no"
    ET_WAY = 0x6177, // "wa"
    ET_RELATION = 0x6572, // "re"
    ET_TAG = 0x6174, // "ta"
    ET_ND = 0x646E, // "nd"
    ET_MEMBER = 0x656D // "me"
  };

  ETag tagKey = ET_UNKNOWN;
  uint64_t id = 0;
  double lon = 0;
  double lat = 0;
  uint64_t ref = 0;
  string k;
  string v;
  string type;
  string role;
  
  vector<XMLElement> childs;

  void Clear()
  {
    tagKey = ET_UNKNOWN;
    id = 0;
    lon = 0;
    lat = 0;
    ref = 0;
    k.clear();
    v.clear();
    type.clear();
    role.clear();

    childs.clear();
  }

  string ToString(string const & shift = string()) const;

  bool operator == (XMLElement const & e) const
  {
    return (
            tagKey == e.tagKey
            && id == e.id
            && my::AlmostEqualAbs(lon, e.lon, 1e-7)
            && my::AlmostEqualAbs(lat, e.lat, 1e-7)
            && ref == e.ref
            && k == e.k
            && v == e.v
            && type == e.type
            && role == e.role
            && childs == childs
    );
  }

  void AddKV(string const & k, string const & v);
  void AddND(uint64_t ref);
  void AddMEMBER(uint64_t ref, string const & type, string const & role);
};

string DebugPrint(XMLElement const & e);

class BaseOSMParser
{
  XMLElement m_parent;
  XMLElement m_child;

  size_t m_depth;

protected:
  XMLElement * m_current;

public:
  BaseOSMParser() : m_depth(0), m_current(0) {}

  void AddAttr(string const & key, string const & value);
  bool Push(string const & tagName);
  void Pop(string const &);
  void CharData(string const &) {}

  virtual void EmitElement(XMLElement * p) = 0;
};
