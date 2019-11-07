#ifndef _UTILS_H
#define _UTILS_H

/*! \file utils.h
 *
 * Des fonctions utilitaires, attachées à aucune structure de données.
 */

#include <stdlib.h>
#include <time.h>

/*! Génère un nombre entier aléatoire dans un intervalle donné.
 *
 * La fonction #rand_ab permet de générer un nombre entier pseudo-aléatoire
 * compris dans l'intervalle [\a a, \a b].
 *
 * \param a un entier, limite inférieure de l'intervalle.
 * \param b un entier, limite supérieure de l'intervalle.
 * \return un entier dans l'intervalle [\a a, \a b].
 *
 * \see rand_ab_f - génération de nombre flottant pseudo_aléatoire
 */
int rand_ab(int a, int b) ;

/*! Retourne le max de deux nombres entiers.
 *
 * \param a un entier.
 * \param b un entier.
 * \return La valeur du plus grand des deux nombres \a a et \a b.
 */
int max(int a, int b) ;

/*! Retourne le min de deux nombres entiers.
 *
 * \param a un entier.
 * \param b un entier.
 * \return La valeur du plus petit des deux nombres \a a et \a b.
 */
int min(int a, int b) ;

/*! Génère un nombre flottant aléatoire dans un intervalle donné.
 *
 * La fonction #rand_ab permet de générer un nombre flottant pseudo-aléatoire
 * compris dans l'intervalle [\a a, \a b].
 *
 * \param a un flottant, limite inférieure de l'intervalle.
 * \param b un flottant, limite supérieure de l'intervalle.
 * \return un flottant dans l'intervalle [\a a, \a b].
 *
 * \see rand_ab - génération de nombre entier pseudo_aléatoire
 */
double rand_ab_f(double a, double b) ;

/*! Retourne le max de deux nombres flottants.
 *
 * \param a un flottant.
 * \param b un flottant.
 * \return La valeur du plus grand des deux nombres \a a et \a b.
 */
float max_f(float a, float b) ;

/*! Retourne le min de deux nombres flottants.
 *
 * \param a un flottant.
 * \param b un flottant.
 * \return La valeur du plus petit des deux nombres \a a et \a b.
 */
float min_f(float a, float b) ;

#endif
