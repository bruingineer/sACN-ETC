/******************************************************************************
 * Copyright 2020 ETC Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************
 * This file is a part of sACN. For more information, go to:
 * https://github.com/ETCLabs/sACN
 *****************************************************************************/

/*!
 * \file sacn/version.h
 * \brief Provides the current version of the sACN library.
 *
 * This file is provided for application use; the values defined in this file are not used
 * internally by the library.
 */

#ifndef SACN_VERSION_H_
#define SACN_VERSION_H_

/* clang-format off */

/*!
 * \addtogroup sACN
 * @{
 */

/*!
 * \name sACN version numbers
 * @{
 */
#define SACN_VERSION_MAJOR 1 /*!< The major version. */
#define SACN_VERSION_MINOR 0 /*!< The minor version. */
#define SACN_VERSION_PATCH 0 /*!< The patch version. */
#define SACN_VERSION_BUILD 6 /*!< The build number. */
/*!
 * @}
 */

/*!
 * \name sACN version strings
 * @{
 */
#define SACN_VERSION_STRING      "1.0.0.6"
#define SACN_VERSION_DATESTR     "01.Oct.2018"
#define SACN_VERSION_COPYRIGHT   "Copyright 2018 Electronic Theatre Controls, Inc."
#define SACN_VERSION_PRODUCTNAME "sACN"
/*!
 * @}
 */

/*!
 * @}
 */

#endif /* SACN_VERSION_H_ */
