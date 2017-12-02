#pragma once

namespace TSP {

	enum class WeightType {
		notSet,
		explicitType,
		euclidean2d,
		euclidean3d,
		max2d,
		max3d,
		man2d,
		man3d,
		ceil2d,
		geo,
		att,
		xray1,
		xray2,
		special
	};

	enum class EdgeWeightFormat {
		notSet,
		function,
		fullMatrix,
		upperRow,
		lowerRow,
		upperDiagRow,
		lowerDiagRow,
		upperCol,
		lowerCol,
		upperDiagCol,
		lowerDiagCol
	};

	enum class Type {
		notSet,
		tsp,
		atsp,
		sop,
		hcp,
		cvrp,
		tour
	};

	enum class EdgeDataFormat {
		notSet,
		edgeList,
		adjList
	};

	enum class NodeCoordType {
		notSet,
		twodCoords,
		threedCoords,
		noCoords
	};

	enum class DisplayDataType {
		notSet,
		coordDisplay,
		twodDisplay,
		noDisplay
	};

	std::string toString(WeightType in);
	std::string toString(EdgeWeightFormat in);
	std::string toString(Type in);
	std::string toString(EdgeDataFormat in);
	std::string toString(NodeCoordType in);
	std::string toString(DisplayDataType in);
};