#ifndef ICARCOMPONENT_H
#define ICARCOMPONENT_H

#include <string>
#include <ostream>


/// @author Thomas Lechner
/// @date 26.11.2026
/// @brief Interface of all components of a rentable car.
class ICarComponent
{
public:
	/// @brief std::unique_ptr of this class.
	using UPtr = std::unique_ptr<ICarComponent>;

	/// @brief Raw const pointer of this class.
	using RPtr = ICarComponent const*;

	/// @brief Gets the total price for this car.
	/// @returns The price of this component and all subcomponents.
	virtual size_t GetPrice() const = 0;

	/// @brief Gets the manufacturer of the car.
	/// @returns The manufacturer of the car's base.
	virtual std::string_view GetManufacturer() const = 0;

	/// @brief Gets the type of the car.
	/// @returns The type of the car's base.
	virtual std::string_view GetType() const = 0;

	/// @brief Prints all information about a car.
	/// @param[inout] ost The std::ostream to print the data to.
	virtual void Print(std::ostream& ost) const = 0;

	/// @brief Virtual DTor.
	virtual ~ICarComponent() = default;
};

#endif