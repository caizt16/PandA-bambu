/*
 *
 *                   _/_/_/    _/_/   _/    _/ _/_/_/    _/_/
 *                  _/   _/ _/    _/ _/_/  _/ _/   _/ _/    _/
 *                 _/_/_/  _/_/_/_/ _/  _/_/ _/   _/ _/_/_/_/
 *                _/      _/    _/ _/    _/ _/   _/ _/    _/
 *               _/      _/    _/ _/    _/ _/_/_/  _/    _/
 *
 *             ***********************************************
 *                              PandA Project
 *                     URL: http://panda.dei.polimi.it
 *                       Politecnico di Milano - DEIB
 *                        System Architectures Group
 *             ***********************************************
 *              Copyright (c) 2004-2017 Politecnico di Milano
 *
 *   This file is part of the PandA framework.
 *
 *   The PandA framework is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
/**
 * @author Pietro Fezzardi <pietrofezzardi@gmail.com>
 */

// include class header
#include "HWDiscrepancyAnalysis.hpp"

// include from ./
#include "Parameter.hpp"

// include from behavior/
#include "call_graph_manager.hpp"
#include "function_behavior.hpp"

// includes from design_flows/backend/ToHDL
#include "language_writer.hpp"

// include from HLS/
#include "hls_manager.hpp"

// include from HLS/vcd/
#include "Discrepancy.hpp"

// include from parser/discrepancy/
#include "parse_discrepancy.hpp"

// include from tree/
#include "behavioral_helper.hpp"

#include "string_manipulation.hpp" // for GET_CLASS

HWDiscrepancyAnalysis::HWDiscrepancyAnalysis(const ParameterConstRef _parameters, const HLS_managerRef _HLSMgr, const DesignFlowManagerConstRef _design_flow_manager)
    : HLS_step(_parameters, _HLSMgr, _design_flow_manager, HLSFlowStep_Type::HW_DISCREPANCY_ANALYSIS),
      Discr(_HLSMgr->RDiscr),
      present_state_name(static_cast<HDLWriter_Language>(_parameters->getOption<unsigned int>(OPT_writer_language)) == HDLWriter_Language::VERILOG ? "_present_state" : "present_state")
{
   debug_level = parameters->get_class_debug_level(GET_CLASS(*this));
}

const std::unordered_set<std::tuple<HLSFlowStep_Type, HLSFlowStepSpecializationConstRef, HLSFlowStep_Relationship>> HWDiscrepancyAnalysis::ComputeHLSRelationships(const DesignFlowStep::RelationshipType relationship_type) const
{
   std::unordered_set<std::tuple<HLSFlowStep_Type, HLSFlowStepSpecializationConstRef, HLSFlowStep_Relationship>> ret;
   switch(relationship_type)
   {
      case DEPENDENCE_RELATIONSHIP:
      {
         ret.insert(std::make_tuple(HLSFlowStep_Type::C_TESTBENCH_EXECUTION, HLSFlowStepSpecializationConstRef(), HLSFlowStep_Relationship::TOP_FUNCTION));
         break;
      }
      case INVALIDATION_RELATIONSHIP:
      case PRECEDENCE_RELATIONSHIP:
      {
         break;
      }
      default:
      {
         THROW_UNREACHABLE("");
         break;
      }
   }
   return ret;
}

DesignFlowStep_Status HWDiscrepancyAnalysis::Exec()
{
   // parse the file containing the C traces
   const std::string& ctrace_filename = Discr->c_trace_filename;
   INDENT_DBG_MEX(DEBUG_LEVEL_PEDANTIC, debug_level, "-->Parsing C trace: " + ctrace_filename);
   parse_discrepancy(ctrace_filename, Discr);
   INDENT_DBG_MEX(DEBUG_LEVEL_PEDANTIC, debug_level, "<--Parsed C trace: " + ctrace_filename);
   return DesignFlowStep_Status::SUCCESS;
}

bool HWDiscrepancyAnalysis::HasToBeExecuted() const
{
   return true;
}
