#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <cmath>

// define a few common uses of the template class
template <typename T> class bin_t : public std::tuple<std::string,T,T>
{
 public:
  bin_t() : std::tuple<std::string,T,T>() {};
  bin_t(std::string n, T a, T b) : std::tuple<std::string,T,T>(n,a,b) {};
  std::string name() const { return std::get<0>(*this); }
  T low()   const { return std::get<1>(*this); }
  T high()  const { return std::get<2>(*this); }
  void print() const {
    std::string l = (this->name()+" = [ "+std::to_string(this->low())+" , "+std::to_string(this->high())+" ]");
    std::cout << l << std::endl;
  }
  bool operator < (const bin_t& ref) const 
  {
    const std::tuple<std::string,T,T> a(this->name(), this->low(), this->high());
    const std::tuple<std::string,T,T> b(ref.name(), ref.low(), ref.high());
    return (bool)(a < b);
  }
};
typedef bin_t<float>  BinF_t;

// associate a set of bins to make an analysis bin
class AnaBin_t : public std::set<BinF_t>
{
 public:
  AnaBin_t() : std::set<BinF_t>() {};
  AnaBin_t(const std::set<BinF_t>& set) : std::set<BinF_t>(set) {};
  BinF_t getbin (const std::string& name) const {
    for (const auto& s : *this) { if (s.name()==name) { return s; } };
    return BinF_t("", -99., -99.);
  };
  BinF_t getbin (const int& i) const {
    return *std::next(this->begin(), i);
  };
  void setbin (const BinF_t& bin) { this->insert(bin); };
  void setbin (const std::string& n, const float& a, const float& b) {
    this->insert(BinF_t(n,a,b));
  };
  void print() const {
    std::string l = "";
    for (const auto& s : *this) { l += (s.name()+" = [ "+std::to_string(s.low())+" , "+std::to_string(s.high())+" ] , "); }
    if (l.rfind("] , ")!=std::string::npos) { l.erase(l.rfind(" , "), 3); }
    std::cout << l << std::endl;
  }
};

typedef std::tuple<std::string, std::string, std::vector<double>> Var_t;
typedef std::vector<Var_t> VarVec_t;
typedef std::map< BinF_t , std::map< BinF_t , VarVec_t > > BinMapMap_t;

// Initialize the binning
BinMapMap_t BINMAP_Psi2S =
  {
   {
    {"NTrack", 10.0, 250.0},
    {
     {
      {"Cand_AbsRap", 0.0, 1.4},
      {
       {"Cand_Pt", "VAR", {6.5, 8.0, 10.0, 12.0, 50.0}},
       {"Cand_Pt", "VAR", {6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_AbsRap", 1.4, 2.4},
      {
       {"Cand_Pt", "VAR", {0.0, 1.5, 3.0, 4.0, 5.0, 6.5, 8.0, 10.0, 12.0, 50.0}},
       {"Cand_Pt", "VAR", {3.0, 50.0}},
       {"Cand_Pt", "VAR", {3.0, 5.0, 6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_Rap", -2.4, -1.4},
      {
       {"Cand_Pt", "VAR", {3.0, 6.5, 50.0}}
      }
     },
     {
      {"Cand_Rap", 1.4, 2.4},
      {
       {"Cand_Pt", "VAR", {3.0, 6.5, 50.0}}
      }
     },
     {
      {"Cand_Pt", 6.5, 50.0},
      {
       {"Cand_RapCM", "VAR", {-2.86, -1.93, -1.2, -0.6, 0.0, 0.6, 1.2, 1.2, 1.93}},
       {"Cand_RapCM", "VAR", {-1.93, 0.0, 1.93}}
      }
     }
    }
   },
   {
    {"NTrack", 10.0, 50.0},
    {
     {
      {"Cand_AbsRap", 0.0, 1.4},
      {
       {"Cand_Pt", "VAR", {6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_AbsRap", 1.4, 2.4},
      {
       {"Cand_Pt", "VAR", {3.0, 5.0, 6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_Pt", 3.0, 6.5},
      {
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}}
      }
     },
     {
      {"Cand_Pt", 6.5, 50.0},
      {
       {"Cand_RapCM", "VAR", {-2.86, -1.93, -1.2, -0.6, 0.0, 0.6, 1.2, 1.2, 1.93}},
       {"Cand_RapCM", "VAR", {-1.93, 0.0, 1.93}},
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}},
      }
     }
    }
   },
   {
    {"NTrack", 50.0, 80.0},
    {
     {
      {"Cand_AbsRap", 0.0, 1.4},
      {
       {"Cand_Pt", "VAR", {6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_AbsRap", 1.4, 2.4},
      {
       {"Cand_Pt", "VAR", {3.0, 5.0, 6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_Pt", 3.0, 6.5},
      {
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}}
      }
     },
     {
      {"Cand_Pt", 6.5, 50.0},
      {
       {"Cand_RapCM", "VAR", {-2.86, -1.93, -1.2, -0.6, 0.0, 0.6, 1.2, 1.2, 1.93}},
       {"Cand_RapCM", "VAR", {-1.93, 0.0, 1.93}},
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}},
      }
     }
    }
   },
   {
    {"NTrack", 80.0, 120.0},
    {
     {
      {"Cand_AbsRap", 0.0, 1.4},
      {
       {"Cand_Pt", "VAR", {6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_AbsRap", 1.4, 2.4},
      {
       {"Cand_Pt", "VAR", {3.0, 5.0, 6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_Pt", 3.0, 6.5},
      {
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}}
      }
     },
     {
      {"Cand_Pt", 6.5, 50.0},
      {
       {"Cand_RapCM", "VAR", {-2.86, -1.93, -1.2, -0.6, 0.0, 0.6, 1.2, 1.2, 1.93}},
       {"Cand_RapCM", "VAR", {-1.93, 0.0, 1.93}},
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}},
      }
     }
    }
   },
   {
    {"NTrack", 120.0, 250.0},
    {
     {
      {"Cand_AbsRap", 0.0, 1.4},
      {
       {"Cand_Pt", "VAR", {6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_AbsRap", 1.4, 2.4},
      {
       {"Cand_Pt", "VAR", {3.0, 5.0, 6.5, 9.0, 50.0}}
      }
     },
     {
      {"Cand_Pt", 3.0, 6.5},
      {
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}}
      }
     },
     {
      {"Cand_Pt", 6.5, 50.0},
      {
       {"Cand_RapCM", "VAR", {-2.86, -1.93, -1.2, -0.6, 0.0, 0.6, 1.2, 1.2, 1.93}},
       {"Cand_RapCM", "VAR", {-1.93, 0.0, 1.93}},
       {"Cand_Rap", "VAR", {-2.4, -1.4, 1.4, 2.4}},
      }
     }
    }
   }
  };

BinMapMap_t BINMAP_General =
  {
   {
    {"NONE", 0.0, 0.0},
    {
     {
      {"NONE", 0.0, 0.0},
      {
       {"Cand_Pt",  "VAR", {0.0, 1.5, 3.0, 4.0, 5.0, 6.5, 8.0, 10.0, 12.0, 50.0}},
       {"Cand_Rap", "FIX", {24, -2.4, 2.4}},
       {"NTrack", "FIX", {20, 0.0, 20.0}},
       {"NTrack", "VAR", {200, 0.0, 400.0}}
      }
     }
    }
   }
  };


bool decayLenCut(const double& pT, const double& y, const bool& muonTrig=true, const double& thr=0.90)
{
  if(muonTrig)
  {
    if(thr>=0.99)
    {
      if(fabs(y)<1.4) { return (-0.2 + (1.5/std::pow(pT, 0.5))); }
      else if(fabs(y)<2.4) { return (-0.3 + (1.5/std::pow(pT, 0.3))); }
    }
    else if(thr==0.95)
    {
      if(fabs(y)<1.4) { return (0.007 + (0.17/std::pow(pT, 0.67))); }
      else if(fabs(y)<2.4) { return (-0.05 + (0.26/std::pow(pT, 0.36))); }
    }
    else if(thr==0.90)
    {
      if(fabs(y)<1.4) { return (0.008 + (0.13/std::pow(pT, 0.73))); }
      else if(fabs(y)<2.4) { return (-0.03 + (0.18/std::pow(pT, 0.35))); }
    }
    else if(thr==0.85)
    {
      if(fabs(y)<1.4) { return (0.009 + (0.11/std::pow(pT, 0.84))); }
      else if(fabs(y)<2.4) { return (-0.03 + (0.14/std::pow(pT, 0.34))); }
    }
  }
  else
  {
    if(thr>=0.99)
    {
      if(fabs(y)<1.4) { return (-0.1 + (2.8/std::pow(pT, 0.8))); }
      else if(fabs(y)<2.4) { return (-0.1 + (1.7/std::pow(pT, 0.4))); }
    }
    else if(thr==0.95)
    {
      if(fabs(y)<1.4) { return (0.021 + (0.8/std::pow(pT, 1.49))); }
      else if(fabs(y)<2.4) { return (-0.07 + (0.28/std::pow(pT, 0.29))); }
    }
    else if(thr==0.90)
    {
      if(fabs(y)<1.4) { return (-0.010 + (0.12/std::pow(pT, 0.43))); }
      else if(fabs(y)<2.4) { return (-0.05 + (0.18/std::pow(pT, 0.30))); }
    }
    else if(thr==0.85)
    {
      if(fabs(y)<1.4) { return (0.003 + (0.11/std::pow(pT, 0.67))); }
      else if(fabs(y)<2.4) { return (-0.04 + (0.14/std::pow(pT, 0.29))); }
    }
  }
  std::cout << "[ERROR] decayLenCut: invalid inputs!" << std::endl;
  return false;
};
