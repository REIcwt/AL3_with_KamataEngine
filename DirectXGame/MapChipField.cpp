#include "MapChipField.h"
#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {
std::map<std::string, MapChipType> mapChipTable = {

    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock},
};
}

// reset the mapchip data
void MapChipField::ResetMapChipData() {
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void MapChipField::LoadMapChipCsv(const std::string& filePath) {

	// Reset
	ResetMapChipData();

	// open file
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// mapchip csv
	std::stringstream mapChipCsv;
	// copy file data
	mapChipCsv << file.rdbuf();
	// close file
	file.close();

	// read the file data
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {

		std::string line;
		getline(mapChipCsv, line);

		std::istringstream line_stream(line);
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			std::string word;
			getline(line_stream, word, ',');

			if (mapChipTable.contains(word)) {
				mapChipData_.data[i][j] = mapChipTable[word];
			}
		}
	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { return Vector3(kStartX + kBlockWidth * xIndex, kBlockHeight * (kNumBlockVirtical - 1 - yIndex), 0); }

MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position) {
	IndexSet indexSet;
	indexSet.xIndex = static_cast<uint32_t>(((position.x - kStartX) + kBlockWidth / 2) / kBlockWidth);
	indexSet.yIndex = static_cast<uint32_t>(kNumBlockVirtical - 1 - (position.y + kBlockHeight / 2) / kBlockHeight);
	return indexSet;
}
