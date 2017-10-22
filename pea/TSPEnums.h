#pragma once

namespace TSP {

	enum WeightType {
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

	enum EdgeWeightFormat {
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

	enum Type {
		tsp,
		atsp,
		sop,
		hcp,
		cvrp,
		tour
	};

	enum EdgeDataFormat {
		edgeList,
		adjList
	};

	enum NodeCoordType {
		twodCoords,
		threedCoords,
		noCoords
	};

	enum DisplayDataType {
		coordDisplay,
		twodDisplay,
		noDisplay
	};
};