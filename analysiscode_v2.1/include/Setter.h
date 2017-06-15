#ifndef setter_h
#define setter_h

#include <iostream>

class Setter{

 public:
  Setter();
  ~Setter();

  //  Int_t goodelectronindex;
  //Int_t returnmeindex;

  //void SetElectronIndex( Int_t );
  //Int_t GetElectronIndex();

 public:
  /*  Int_t goldenindex() const { return _goldenindex ; }
  void  goldenindex( const Int_t& goldenindex ) { _goldenindex = goldenindex; std::cout << " my golden electron index is " << _goldenindex << std::endl;}
 private:
  Int_t _goldenindex;
  */
  int gold;
  void SetGoldenIndex( int val ){
    this->gold = val;
  }

  int GetGoldenIndex(){
    return this->gold;
  }

};

#endif
