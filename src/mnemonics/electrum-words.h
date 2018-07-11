#pragma once

#include <string>
#include <cstdint>
#include <map>
#include "crypto/crypto.h"  // for declaration of Crypto::SecretKey

namespace Crypto {
namespace ElectrumWords
{

const int seed_length = 24;
const std::string old_language_name = "English";
/*!
	* \brief Converts seed words to bytes (secret key).
	* \param  words           String containing the words separated by spaces.
	* \param  dst             To put the secret key restored from the words.
	* \param  language_name   Language of the seed as found gets written here.
	* \return                 false if not a multiple of 3 words, or if word is not in the words list
	*/
bool words_to_bytes(std::string words, Crypto::SecretKey& dst,
	std::string &language_name);

/*!
	* \brief Converts bytes (secret key) to seed words.
	* \param  src           Secret key
	* \param  words         Space delimited concatenated words get written here.
	* \param  language_name Seed language name
	* \return               true if successful false if not. Unsuccessful if wrong key size.
	*/
bool bytes_to_words(const Crypto::SecretKey& src, std::string& words,
	const std::string &language_name);

/*!
	* \brief Gets a list of seed languages that are supported.
	* \param languages A vector is set to the list of languages.
	*/
void get_language_list(std::vector<std::string> &languages);

/*!
	* \brief Tells if the seed passed is an old style seed or not.
	* \param  seed The seed to check (a space delimited concatenated word list)
	* \return      true if the seed passed is a old style seed false if not.
	*/
bool get_is_old_style_seed(std::string seed);

} //ElectrumWords
} //Crypto

