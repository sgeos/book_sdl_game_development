#ifndef LAYER_H
#define LAYER_H

class Layer {
  public:
    virtual void render(void) = 0;
    virtual void update(void) = 0;

  protected:
    virtual ~Layer(void) { };
};

#endif // LAYER_H

