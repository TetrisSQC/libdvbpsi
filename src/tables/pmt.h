/*****************************************************************************
 * pmt.h: PMT structures
 *----------------------------------------------------------------------------
 * (c)2001-2002 VideoLAN
 * $Id: pmt.h,v 1.1 2002/01/22 20:30:16 bozo Exp $
 *
 * Authors: Arnaud de Bossoreille de Ribou <bozo@via.ecp.fr>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *----------------------------------------------------------------------------
 *
 *****************************************************************************/

#ifndef _DVBPSI_PMT_H_
#define _DVBPSI_PMT_H_


/*****************************************************************************
 * dvbpsi_pmt_es_t
 *****************************************************************************
 * This structure is used to store a decoded ES description.
 * (ISO/IEC 13818-1 section 2.4.4.8).
 *****************************************************************************/
typedef struct dvbpsi_pmt_es_s
{
  uint8_t                       i_type;                 /* stream_type */
  uint16_t                      i_pid;                  /* elementary_PID */

  dvbpsi_descriptor_t *         p_first_descriptor;     /* descriptor list */

  struct dvbpsi_pmt_es_s *      p_next;

} dvbpsi_pmt_es_t;


/*****************************************************************************
 * dvbpsi_pmt_t
 *****************************************************************************
 * This structure is used to store a decoded PMT.
 * (ISO/IEC 13818-1 section 2.4.4.8).
 *****************************************************************************/
typedef struct dvbpsi_pmt_s
{
  uint16_t                  i_program_number;   /* program_number */
  uint8_t                   i_version;          /* version_number */
  int                       b_current_next;     /* current_next_indicator */

  uint16_t                  i_pcr_pid;          /* PCR_PID */

  dvbpsi_descriptor_t *     p_first_descriptor; /* descriptor list */

  dvbpsi_pmt_es_t *         p_first_es;         /* ES list */

} dvbpsi_pmt_t;


/*****************************************************************************
 * dvbpsi_pmt_callback
 *****************************************************************************
 * Callback type definition.
 *****************************************************************************/
typedef void (* dvbpsi_pmt_callback)(void* p_cb_data, dvbpsi_pmt_t* p_new_pmt);


/*****************************************************************************
 * dvbpsi_AttachPMT
 *****************************************************************************
 * Initialize a PMT decoder and return a handle on it.
 *****************************************************************************/
dvbpsi_handle dvbpsi_AttachPMT(uint16_t i_program_number,
                               dvbpsi_pmt_callback pf_callback,
                               void* p_cb_data);


/*****************************************************************************
 * dvbpsi_DetachPMT
 *****************************************************************************
 * Close a PMT decoder. The handle isn't valid any more.
 *****************************************************************************/
void dvbpsi_DetachPMT(dvbpsi_handle h_dvbpsi);


/*****************************************************************************
 * dvbpsi_InitPMT/dvbpsi_NewPMT
 *****************************************************************************
 * Initialize a pre-allocated/new dvbpsi_pmt_t structure.
 *****************************************************************************/
void dvbpsi_InitPMT(dvbpsi_pmt_t* p_pmt, uint16_t i_program_number,
                    uint8_t i_version, int b_current_next, uint16_t i_pcr_pid);

#define dvbpsi_NewPMT(p_pmt, i_program_number,                          \
                      i_version, b_current_next, i_pcr_pid)             \
  p_pmt = (dvbpsi_pmt_t*)malloc(sizeof(dvbpsi_pmt_t));                  \
  if(p_pmt != NULL)                                                     \
    dvbpsi_InitPMT(p_pmt, i_program_number, i_version, b_current_next,  \
                   i_pcr_pid);


/*****************************************************************************
 * dvbpsi_EmptyPMT/dvbpsi_DeletePMT
 *****************************************************************************
 * Clean/free a dvbpsi_pmt_t structure.
 *****************************************************************************/
void dvbpsi_EmptyPMT(dvbpsi_pmt_t* p_pat);

#define dvbpsi_DeletePMT(p_pmt)                                         \
  dvbpsi_EmptyPMT(p_pmt);                                               \
  free(p_pmt);


/*****************************************************************************
 * dvbpsi_PMTAddDescriptor
 *****************************************************************************
 * Add a descriptor in the PMT.
 *****************************************************************************/
dvbpsi_descriptor_t* dvbpsi_PMTAddDescriptor(dvbpsi_pmt_t* p_pmt,
                                             uint8_t i_tag, uint8_t i_length,
                                             uint8_t* p_data);


/*****************************************************************************
 * dvbpsi_PMTAddES
 *****************************************************************************
 * Add an ES in the PMT.
 *****************************************************************************/
dvbpsi_pmt_es_t* dvbpsi_PMTAddES(dvbpsi_pmt_t* p_pmt,
                                 uint8_t i_type, uint16_t i_pid);


/*****************************************************************************
 * dvbpsi_PMTESAddDescriptor
 *****************************************************************************
 * Add a descriptor in the PMT ES.
 *****************************************************************************/
dvbpsi_descriptor_t* dvbpsi_PMTESAddDescriptor(dvbpsi_pmt_es_t* p_es,
                                               uint8_t i_tag, uint8_t i_length,
                                               uint8_t* p_data);


/*****************************************************************************
 * dvbpsi_GenPMTSections
 *****************************************************************************
 * Generate PMT sections based on the dvbpsi_pmt_t structure.
 *****************************************************************************/
dvbpsi_psi_section_t* dvbpsi_GenPMTSections(dvbpsi_pmt_t* p_pmt);


#else
#error "Multiple inclusions of pmt.h"
#endif
