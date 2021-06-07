/******************************************************************************
 * Copyright 2021 ETC Inc.
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

#include "sacn/private/mem/source/unicast_destination.h"

#include <stddef.h>
#include "etcpal/common.h"
#include "etcpal/rbtree.h"
#include "sacn/private/common.h"
#include "sacn/private/opts.h"
#include "sacn/private/mem/common.h"

#if SACN_DYNAMIC_MEM
#include <stdlib.h>
#else
#include "etcpal/mempool.h"
#endif

#if SACN_SOURCE_ENABLED

/*********************** Private function prototypes *************************/

static size_t get_unicast_dest_index(SacnSourceUniverse* universe, const EtcPalIpAddr* addr, bool* found);

/*************************** Function definitions ****************************/

// Needs lock
etcpal_error_t add_sacn_unicast_dest(SacnSourceUniverse* universe, const EtcPalIpAddr* addr,
                                     SacnUnicastDestination** dest_state)
{
  etcpal_error_t result = kEtcPalErrOk;
  SacnUnicastDestination* dest = NULL;

  if (lookup_unicast_dest(universe, addr, &dest) == kEtcPalErrOk)
    result = kEtcPalErrExists;

  if (result == kEtcPalErrOk)
  {
    CHECK_ROOM_FOR_ONE_MORE(universe, unicast_dests, SacnUnicastDestination, SACN_MAX_UNICAST_DESTINATIONS_PER_UNIVERSE,
                            kEtcPalErrNoMem);

    dest = &universe->unicast_dests[universe->num_unicast_dests++];
    dest->dest_addr = *addr;
    dest->termination_state = kNotTerminating;
    dest->num_terminations_sent = 0;
  }

  *dest_state = dest;

  return result;
}

// Needs lock
etcpal_error_t lookup_unicast_dest(SacnSourceUniverse* universe, const EtcPalIpAddr* addr,
                                   SacnUnicastDestination** unicast_dest)
{
  bool found = false;
  size_t index = get_unicast_dest_index(universe, addr, &found);
  *unicast_dest = found ? &universe->unicast_dests[index] : NULL;
  return found ? kEtcPalErrOk : kEtcPalErrNotFound;
}

// Needs lock
void remove_sacn_unicast_dest(SacnSourceUniverse* universe, size_t index)
{
  REMOVE_AT_INDEX(universe, SacnUnicastDestination, unicast_dests, index);
}

size_t get_unicast_dest_index(SacnSourceUniverse* universe, const EtcPalIpAddr* addr, bool* found)
{
  *found = false;
  size_t index = 0;

  while (!(*found) && (index < universe->num_unicast_dests))
  {
    if (etcpal_ip_cmp(&universe->unicast_dests[index].dest_addr, addr) == 0)
      *found = true;
    else
      ++index;
  }

  return index;
}

#endif  // SACN_SOURCE_ENABLED
