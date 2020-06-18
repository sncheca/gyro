#ifndef HRTFASSETS_
#define HRTFASSETS_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sadie {

// Note this class is automatically generated. Do not modify.
class HrtfAssets {
 public:
  // Lookups and retrieves a file from an asset class.
  //
  // @param filename: Filename to be retrieved.
  // @return std::string with raw file data. In case of an error, a nullptr is
  //     returned. Caller must take over the ownership of the returned data.
  std::unique_ptr<std::string> GetFile(const std::string& filename) const;

 private:
  typedef std::unordered_map<std::string, std::vector<unsigned char>>
      AssetDataMap;
  static const AssetDataMap kAssetMap;
};

}  // namespace sadie

#endif  // HRTFASSETS_
