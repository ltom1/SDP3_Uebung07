#include "CarRental.h"

static auto constexpr cErrNullptr  = "Provided car was nullptr";
static auto constexpr cErrNotFound = "Provided car was not found";

void CarRental::Add(ICarComponent::UPtr car)
{
	if (car == nullptr) throw std::invalid_argument(cErrNullptr);

	mAvailable.emplace_back(std::move(car));
}

void CarRental::PrintAvailable(std::ostream& ost) const
{
	for (auto const& car : mAvailable)
	{
		car->Print(ost);
	}
}

void CarRental::PrintReserved(std::ostream& ost) const
{
	for (auto const& car : mReserved)
	{
		car->Print(ost);
	}
}

std::vector<ICarComponent::RPtr> CarRental::GetAvailable(std::string const& manufacturer, std::string const& type) const
{
	return FindCars(mAvailable, manufacturer, type);
}

std::vector<ICarComponent::RPtr> CarRental::GetReserved(std::string const& manufacturer, std::string const& type) const
{
	return FindCars(mReserved, manufacturer, type);
}

void CarRental::Reserve(ICarComponent::RPtr const car)
{
	MoveCar(mAvailable, mReserved, car);
}

void CarRental::Back(ICarComponent::RPtr const car)
{
	MoveCar(mReserved, mAvailable, car);
}

std::vector<ICarComponent::RPtr> CarRental::FindCars(std::vector<ICarComponent::UPtr> const& cars, std::string const& manufacturer, std::string const& type) const
{
	std::vector<ICarComponent::RPtr> results;

	// Loop through all cars.
	for (auto const& car : cars)
	{
		// Does it have the requirements?
		if (car->GetManufacturer() == manufacturer && car->GetType() == type)
		{
			results.push_back(car.get());
		}
	}

	return results;
}

void CarRental::MoveCar(std::vector<ICarComponent::UPtr>& from, std::vector<ICarComponent::UPtr>& to, ICarComponent::RPtr const car) const
{
	// Try to find the car in the source container.
	auto const itor = std::find_if(from.begin(), from.end(), [car](auto const& elem) {
		return elem.get() == car;
	});

	// The car was not found in the source container.
	if (itor == from.end()) throw std::runtime_error(cErrNotFound);

	// It was found! -> Move it into the destination container.
	to.emplace_back(std::move(*itor));
	from.erase(itor);
}