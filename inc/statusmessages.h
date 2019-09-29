// -*- C++ -*-
/**
* @author Zach Pearson
* @file   statusmessages.h
* @date   29 September 2019
* @brief
*/

#ifndef STATUSMESSAGES_H
#define STATUSMESSAGES_H

class StatusMessages {

    public:

	/**
	 * @brief At game start ask players how many ships they want.
	 */
	static void AskNumShips();

	/**
	 * @brief Print an error if the players choose an invalid num ships
	 */
	static void ErrorNumShips();

	/**
	 * @brief Ask what orientation the player wants for a particular ship.
	 */
	static void AskDirection();

	/**
	 * @brief Asks the player where they want their ship to go
	 * @param player to whom we are showing this message.
	 * @param ship the ship we are asking about
	 */
	static void AskForShip(int player, int ship);

	/**
	 * @brief Display error message if user cannot count to 8.
	 */
	static void ErrorInvalidRow();

	/**
	 * @brief Display error message if user does not know the alphabet.
	 */
	static void ErrorInvalidCol();

	/**
	 * @brief Prints an error message when the player selects a location for
	 *        their ship which is already serving as the root location for
	 *        another ship.
	 */
	static void ShipAlreadyThere();

	/**
	 * @brief Prints an error message similar to ShipAlreadyThere(), except
	 *        this triggers when the original root was valid, but the
	 *        chosen direction causes a collision with another ship.
	 */
	static void ShipInTheWay();

	/**
	 * @brief Notifies the player that they have already shot at the place
	 *        they are trying to shoot at
	 */
	static void AlreadyShotThere();

	/**
	 * @brief If the player hits a ship, confirm it.
	 */
	static void ConfirmHit();

	/**
	 * @brief If the player does not hit a ship, inform them.
	 */
	static void ConfirmMiss();

	/**
	 * @brief Notifies players of a turn change.
	 */
	static void NextPlayer();

};

#endif // STATUSMESSAGES_H_
