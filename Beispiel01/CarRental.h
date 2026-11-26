#ifndef ICARRENTAL_H
#define ICARRENTAL_H

#include "ICarComponent.h"

#include <string>
#include <ostream>
#include <vector>


/// @author Thomas Lechner
/// @date 26.11.2026
/// @brief Manages multiple cars for a car rental.
/// 
/// Has functionality for adding new, reserving, bringing back rentable cars.
/// Cannot be copied or reassigned.
class CarRental
{
public:
	/// @brief Default CTor.
	CarRental() = default;

	/// @brief Disallow copying.
	CarRental(CarRental const&) = delete;

	/// @brief Disallow assigning.
	CarRental& operator=(CarRental const&) = delete;

	/// @brief Adds a new car to the car rental.
	/// @param[in] car The car to add.
	/// 
	/// The car is immediately available and rentable after adding.
	void Add(ICarComponent::UPtr car);


	/// @brief Prints all available cars.
	/// @param[inout] ost The std ::ostream to print the information to.
	void PrintAvailable(std::ostream& ost) const;

	/// @brief Prints all reserved cars.
	/// @param[inout] ost The std::ostream to print the information to.
	void PrintReserved(std::ostream& ost) const;


	/// @brief Returns all available cars from the provided manufacturer and of the provided type.
	/// @param[in] manufacturer The manufacturer to search for.
	/// @param[in] type The car type to search for.
	/// @returns A std::vector of raw pointers to all available cars that fit the provided criteria.
	std::vector<ICarComponent::RPtr> GetAvailable(std::string const& manufacturer, std::string const& type) const;

	/// @brief Returns all reserved cars from the provided manufacturer and of the provided type.
	/// @param[in] manufacturer The manufacturer to search for.
	/// @param[in] type The car type to search for.
	/// @returns A std::vector of raw pointers to all reserved cars that fit the provided criteria.
	std::vector<ICarComponent::RPtr> GetReserved(std::string const& manufacturer, std::string const& type) const;


	/// @brief Reserves a car that is available.
	/// @param[in] car The car to reserve.
	/// 
	/// If the car is not available, an exception is thrown. Only pass cars you got from the GetAvailable methods.
	void Reserve(ICarComponent::RPtr const car);

	/// @brief Returns a car that was reserved.
	/// @param[in] car The car to return.
	/// 
	/// If the car is not reserved, an exception is thrown. Only pass cars you got from the GetReserved methods.
	void Back(ICarComponent::RPtr const car);
	
private:
	/// @brief List of all cars that are currently available for renting.
	std::vector<ICarComponent::UPtr> mAvailable;

	/// @brief List of all cars that are currently rented/reserved.
	std::vector<ICarComponent::UPtr> mReserved;

	/// @brief Returns all cars from the provided manufacturer and of the provided type.
	/// @param[in] cars The list of cars to search through.
	/// @param[in] manufacturer The manufacturer to search for.
	/// @param[in] type The car type to search for.
	/// @returns A std::vector of raw pointers to all cars that fit the provided criteria.
	std::vector<ICarComponent::RPtr> FindCars(std::vector<ICarComponent::UPtr> const& cars, std::string const& manufacturer, std::string const& type) const;

	/// @brief Moves a car from one container to the other if it exists.
	/// @param[inout] from The source container.
	/// @param[inout] to The destination container.
	/// @param[in] car The car to move.
	/// 
	/// If the car is not in the source container, an exception is thrown. 
	void MoveCar(std::vector<ICarComponent::UPtr>& from, std::vector<ICarComponent::UPtr>& to, ICarComponent::RPtr const car) const;
};

#endif