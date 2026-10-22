#ifndef LAB5_TEMPLATES_H_
#define LAB5_TEMPLATES_H_

#include <utility>

template <typename TId, typename TName, typename TObject, typename TMetric,
          typename TState>
class ProjectRecord {
public:
  ProjectRecord(TId id, TName name, TObject object, TMetric metric,
                TState state)
      : id_(std::move(id)), name_(std::move(name)), object_(std::move(object)),
        metric_(std::move(metric)), state_(std::move(state)) {}

  const TId &GetId() const { return id_; }
  const TName &GetName() const { return name_; }
  const TObject &GetObject() const { return object_; }
  const TMetric &GetMetric() const { return metric_; }
  const TState &GetState() const { return state_; }

private:
  TId id_;
  TName name_;
  TObject object_;
  TMetric metric_;
  TState state_;
};

#endif
