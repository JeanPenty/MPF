
inline MeasureData* Element::GetMeasureData()
{
    return &_measureData;
}

inline EventHandlersStore* Element::GetEventHandlersStore()
{
    return _evthStore;
}

inline fRect& Element::GetDescendantBounds()
{
    return _descendantBounds;
}

inline bool Element::IsClipToBounds()
{
    return ReadDoFlag(ViewFlags::IsClipToBoundsVF);
}

inline bool Element::ReadFlag(int key) const
{
    return (0 != (_flag & key));
}

inline Element* Element::GetUIParent() const
{
    return (Element*)(_parent.GetTarget());
}

inline DpObject* Element::GetContextParent() const
{
    return GetUIParent();
}

inline void Element::ResetCanvasOffset()
{
    _canvasOffset.x = 0;
    _canvasOffset.y = 0;
}

inline fPoint Element::GetCanvasOffset() const
{
    return _canvasOffset;
}

inline fSize Element::GetRenderSize()
{
    if (Visibility::Collapsed != GetVisibility())
    {
        return _renderSize;
    }
    else
    {
        return fSize();
    }
}

inline fSize Element::ComputeRenderSize()
{
    return GetRenderSize();
}

inline fRect Element::GetRenderRect()
{
    if (Visibility::Collapsed != GetVisibility())
    {
        return fRect(0, 0, _renderSize.cx, _renderSize.cy);
    }
    else
    {
        return fRect(0, 0, 0, 0);
    }
}

inline Float Element::GetActualWidth()
{
    return _renderSize.cx;
}

inline Float Element::GetActualHeight()
{
    return _renderSize.cy;
}

inline bool Element::IsInitialized()
{
    return ReadFlag(CoreFlags::IsInitialized);
}

inline bool Element::IsLoaded()
{
    return ReadFlag(CoreFlags::IsLoaded);
}

inline bool Element::IsCollapsed()
{
    return ReadFlag(CoreFlags::IsCollapsed);
}

inline void Element::SetIsCollapsed(bool val)
{
    WriteFlag(CoreFlags::IsCollapsed, val);
}

inline void Element::AddHandler(const RoutedEvent* routedEvent, Handler* handler)
{
    AddHandler(routedEvent, handler, false);
}

inline bool DpObject::ReadDoFlag(Uint32 key) const
{
    return (key == (_viewflag & key));
}

inline fPoint Element::GetVisualOffset() const
{
    return _offset;
}

inline void Element::SetVisualOffset(const fPoint& pt)
{
    _offset.x = pt.x;
    _offset.y = pt.y;
}

inline int Element::GetParentIndex() const
{
    return _parentIndex;
}

inline bool Element::GetCacheLayer()
{
    return GetValue(CacheLayerProperty)->ToBool();
}

inline void Element::SetCacheLayer(bool val)
{
    SetValue(CacheLayerProperty, BOOLTOBOOLEAN(val));
}

inline RenderContext* Element::GetRenderContext() const
{
    return _renderLayer;
}
