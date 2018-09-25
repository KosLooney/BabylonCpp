#ifndef BABYLON_CORE_JSON_H
#define BABYLON_CORE_JSON_H

#include <deque>

#include <babylon/babylon_api.h>
#include <babylon/utils/picojson.h>

namespace picojson {
class value;
typedef std::vector<value> array;
typedef std::map<std::string, value> object;
} // end of namespace picojson

namespace BABYLON {
namespace Json {

typedef picojson::value value;
typedef picojson::array array;
typedef picojson::object object;

inline std::string Parse(Json::value& parsedData, const std::string& json)
{
  return picojson::parse(parsedData, json);
}

template <typename T>
inline picojson::value ToJson(const std::deque<T>& items)
{
  picojson::array arr;

  for (const auto& i : items) {
    arr.push_back(picojson::value(i));
  }

  return picojson::value(arr);
}

template <typename T>
inline std::deque<T>& FromJson(std::deque<T>& items,
                               const picojson::value& input)
{
  if (input.is<picojson::array>()) {
    const auto& array = input.get<picojson::array>();
    for (const auto& a : array) {
      items.push_back(a.get<T>());
    }
  }

  return items;
}

template <class T,
          typename std::enable_if<std::is_same<T, int>::value, int>::type
          = 0>
inline std::pair<std::string, picojson::value> Pair(const std::string& name,
                                                    int value)
{
  return std::make_pair(name, picojson::value(static_cast<double>(value)));
}

template <class T, typename std::enable_if<
                     std::is_same<T, unsigned int>::value, unsigned int>::type
                   = 0>
inline std::pair<std::string, picojson::value> Pair(const std::string& name,
                                                    unsigned int value)
{
  return std::make_pair(name, picojson::value(static_cast<double>(value)));
}

template <
  class T,
  typename std::enable_if<std::is_same<T, size_t>::value, size_t>::type = 0>
inline std::pair<std::string, picojson::value> Pair(const std::string& name,
                                                    size_t value)
{
  return std::make_pair(name, picojson::value(static_cast<double>(value)));
}

template <class T,
          typename std::enable_if<!std::is_same<T, int>::value, int>::type
          = 0>
inline std::pair<std::string, picojson::value> Pair(const std::string& name,
                                                    const T& value)
{
  return std::make_pair(name, picojson::value(value));
}

template <class T,
          typename std::enable_if<std::is_same<T, int>::value, int>::type
          = 0>
inline Json::value NameValuePair(const std::string& name, int value)
{
  return picojson::value(
    picojson::object{{"name", picojson::value(name)},
                     {"value", picojson::value(static_cast<double>(value))}});
}

template <class T,
          typename std::enable_if<!std::is_same<T, int>::value, int>::type
          = 0>
inline Json::value NameValuePair(const std::string& name, const T& value)
{
  return picojson::value(picojson::object{{"name", picojson::value(name)},
                                          {"value", picojson::value(value)}});
}

template <typename T>
inline T GetNumber(const picojson::value& v, const std::string& key,
                   T defaultValue)
{
  if (v.contains(key)) {
    return static_cast<T>(v.get(key).get<double>());
  }
  else {
    return defaultValue;
  }
}

inline bool GetBool(const picojson::value& v, const std::string& key,
                    bool defaultValue = false)
{
  if (v.contains(key)) {
    return v.get(key).get<bool>();
  }
  else {
    return defaultValue;
  }
}

inline std::string GetString(const picojson::value& v, const std::string& key,
                             const std::string& defaultValue = "")
{
  if (v.contains(key)) {
    return v.get(key).get<std::string>();
  }
  else {
    return defaultValue;
  }
}

inline Json::array GetArray(const picojson::value& v, const std::string& key)
{
  if (v.contains(key) && v.get(key).is<Json::array>()) {
    return v.get(key).get<Json::array>();
  }
  return Json::array();
}

template <typename T>
inline std::vector<T> ToArray(const picojson::value& v, const std::string& key)
{
  std::vector<T> array;
  if (v.contains(key) && (v.get(key).is<picojson::array>())) {
    array.reserve(v.get(key).get<picojson::array>().size());
    for (auto& element : v.get(key).get<picojson::array>()) {
      array.emplace_back(static_cast<T>(element.get<double>()));
    }
  }
  return array;
}

inline std::vector<std::string> ToStringVector(const picojson::value& v,
                                               const std::string& key)
{
  std::vector<std::string> stringVector;
  if (v.contains(key) && (v.get(key).is<picojson::array>())) {
    stringVector.reserve(v.get(key).get<picojson::array>().size());
    for (auto& element : v.get(key).get<picojson::array>()) {
      stringVector.emplace_back(element.get<std::string>());
    }
  }
  return stringVector;
}

} // namespace Json
} // end of namespace BABYLON

#endif // end of BABYLON_CORE_STRING_H
