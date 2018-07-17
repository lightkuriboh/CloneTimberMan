#pragma once
#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
class PieceReader : public cocostudio::NodeReader
{
	public:
		static PieceReader* getInstance();
		static void purge();
		cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
		
};

