#include "fans/Planar.h"

Planar::Planar(const double circularDuctDiameter, const double tdx, const double pbx, const double psx)
		: tdx(tdx), pbx(pbx), area(((3.14159265358979 / 4) * (circularDuctDiameter * circularDuctDiameter)) / 144.0),
		  psx(psx)
{}

Planar::Planar(const double length, const double width, const double tdx, const double pbx, const double psx,
               const unsigned noInletBoxes)
		: tdx(tdx), pbx(pbx), area((length * width * noInletBoxes) / 144.0), psx(psx)
{}

FanInletFlange::FanInletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
		: Planar(circularDuctDiameter, tdx, pbx, 0) {}

FanInletFlange::FanInletFlange(const double length, const double width, const double tdx, const double pbx,
                               const unsigned noInletBoxes)
		: Planar(length, width, tdx, pbx, 0, noInletBoxes)
{}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
		: Planar(circularDuctDiameter, tdx, pbx, 0) {}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double length, const double width,
                                               const double tdx, const double pbx, const unsigned noInletBoxes)
		: Planar(length, width, tdx, pbx, 0, noInletBoxes)
{}

FlowTraverse::FlowTraverse(const double circularDuctDiameter, const double tdx, const double pbx,
                           const double psx, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > traverseHoleData)
		: Planar(circularDuctDiameter, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, std::move(traverseHoleData))
{}

FlowTraverse::FlowTraverse(const double length, const double width, const double tdx, const double pbx,
                           const double psx, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > traverseHoleData, const unsigned noInletBoxes)
		: Planar(length, width, tdx, pbx, psx, noInletBoxes),
		  VelocityPressureTraverseData(pitotTubeCoefficient, std::move(traverseHoleData))
{}

AddlTravPlane::AddlTravPlane(const double circularDuctDiameter, const double tdx, const double pbx,
                             const double psx, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > traverseHoleData)
		: Planar(circularDuctDiameter, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, std::move(traverseHoleData))
{}

AddlTravPlane::AddlTravPlane(const double length, const double width, const double tdx, const double pbx,
                             const double psx, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > traverseHoleData, const unsigned noInletBoxes)
		: Planar(length, width, tdx, pbx, psx, noInletBoxes),
		  VelocityPressureTraverseData(pitotTubeCoefficient, std::move(traverseHoleData))
{}

InletMstPlane::InletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx, const double psx)
		: Planar(circularDuctDiameter, tdx, pbx, psx) {}

InletMstPlane::InletMstPlane(const double length, const double width, const double tdx, const double pbx,
                             const double psx, const unsigned noInletBoxes)
		: Planar(length, width, tdx, pbx, psx, noInletBoxes)
{}

OutletMstPlane::OutletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx,
                               const double psx)
		: Planar(circularDuctDiameter, tdx, pbx, psx) {}

OutletMstPlane::OutletMstPlane(const double length, const double width, const double tdx, const double pbx,
                               const double psx, const unsigned noInletBoxes)
		: Planar(length, width, tdx, pbx, psx, noInletBoxes)
{}

VelocityPressureTraverseData::VelocityPressureTraverseData(const double pitotTubeCoefficient,
                                                           std::vector< std::vector< double > > traverseHoleData)
		: pitotTubeCoefficient(pitotTubeCoefficient), traverseHoleData(std::move(traverseHoleData))
{
	auto maxPv3r = 0.0;
	auto sumPv3r = 0.0;
	for (auto & row : this->traverseHoleData) {
		for (auto & val : row) {
			if (val <= 0) {
				val = 0;
				continue;
			}
			val *= std::pow(pitotTubeCoefficient, 2);
			if (val > maxPv3r) maxPv3r = val;
			sumPv3r += std::sqrt(val);
		}
	}

	// TODO this pv3 value differs slightly from what is in the document
	pv3 = std::pow(sumPv3r / (this->traverseHoleData.size() * this->traverseHoleData[0].size()), 2);

	std::size_t count = 0;
	for (auto & row : this->traverseHoleData) {
		for (auto & val : row) {
			if (val > (0.1 * maxPv3r)) count++;
		}
	}

	percent75Rule = count / static_cast<double>(this->traverseHoleData.size() * this->traverseHoleData[0].size());
}