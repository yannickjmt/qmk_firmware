/* Copyright 2017 Benjamin Kesselring
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once


#define TAPPING_TOGGLE 2
// Key must be released within this many milliseconds to be considered a tap
#define TAPPING_TERM 300

// - after 1.5s, turn off one-shot keys
#define ONESHOT_TIMEOUT 1500
#define ONESHOT_TAP_TOGGLE 5


#define PREVENT_STUCK_MODIFIERS

#define PERMISSIVE_HOLD
