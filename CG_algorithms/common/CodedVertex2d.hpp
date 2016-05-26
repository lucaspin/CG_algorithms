/**
 * CodedVertex2d.hpp
 * We extend this class from Vertex2d, adding a regionCode field,
 * to implement the Cohen-Sutherland algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef CodedVertex2d_hpp
#define CodedVertex2d_hpp

#include "CodedVertex2d.hpp"
#include "Vertex2d.hpp"
#include <vector>

class CodedVertex2d : public Vertex2d {
private:
    std::vector<bool> regionCode;
public:
    CodedVertex2d(float x, float y, float z);
    CodedVertex2d(float x, float y);
    void setRegionCode(std::vector<bool> _regionCode);
    std::vector<bool> getRegionCode();
    void setTopRegionCode(bool _state);
    void setBottomRegionCode(bool _state);
    void setRightRegionCode(bool _state);
    void setLeftRegionCode(bool _state);
    bool getTopRegionCode();
    bool getBottomRegionCode();
    bool getRightRegionCode();
    bool getLeftRegionCode();    
};
#endif /* CodedVertex2d_hpp */
