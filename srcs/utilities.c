/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utilities.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 15:44:14 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 15:44:46 by flombard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

Uint32	ft_rgba(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	r = red & 0xFF;
	g = green & 0xFF;
	b = blue & 0xFF;
	a = alpha & 0xFF;
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

Uint32	ft_argb_to_rgba(Uint32 pixel)
{
	return (((pixel >> 24) & 0xFF) | (pixel << 8));
}
