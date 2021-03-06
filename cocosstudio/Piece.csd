<GameFile>
  <PropertyGroup Name="Piece" Type="Node" ID="582f6e91-fed8-4b9a-8260-b98f8df05403" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="96" Speed="1.0000" ActivedAnimationName="default">
        <Timeline ActionTag="2124424664" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="48" X="800.0000" Y="200.0000">
            <EasingData Type="5" />
          </PointFrame>
          <PointFrame FrameIndex="49" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="96" X="-800.0000" Y="200.0000">
            <EasingData Type="2" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="2124424664" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="1" X="1.0000" Y="1.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="48" X="1.0000" Y="1.0000">
            <EasingData Type="5" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="49" X="1.0000" Y="1.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="96" X="1.0000" Y="1.0000">
            <EasingData Type="2" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="2124424664" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="48" X="120.0000" Y="120.0000">
            <EasingData Type="5" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="49" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="96" X="-120.0000" Y="-120.0000">
            <EasingData Type="2" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="default" StartIndex="0" EndIndex="0">
          <RenderColor A="255" R="255" G="182" B="193" />
        </AnimationInfo>
        <AnimationInfo Name="moveRight" StartIndex="1" EndIndex="48">
          <RenderColor A="255" R="240" G="230" B="140" />
        </AnimationInfo>
        <AnimationInfo Name="moveLeft" StartIndex="49" EndIndex="96">
          <RenderColor A="255" R="0" G="0" B="139" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="12" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="roll" ActionTag="2124424664" Tag="13" IconVisible="False" LeftMargin="-105.0000" RightMargin="-105.0000" TopMargin="-122.5000" BottomMargin="-122.5000" ctype="SpriteObjectData">
            <Size X="210.0000" Y="245.0000" />
            <Children>
              <AbstractNodeData Name="leftChopstick" ActionTag="-339078889" VisibleForFrame="False" Tag="14" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-210.0000" RightMargin="210.0000" TopMargin="101.5000" BottomMargin="52.5000" ctype="SpriteObjectData">
                <Size X="210.0000" Y="91.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position Y="98.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="0.4000" />
                <PreSize X="1.0000" Y="0.3714" />
                <FileData Type="Normal" Path="Assets/Images/resources-2x/chopstick.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="rightChopstick" ActionTag="1218295663" VisibleForFrame="False" Tag="15" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="210.0000" RightMargin="-210.0000" TopMargin="101.5000" BottomMargin="52.5000" FlipX="True" ctype="SpriteObjectData">
                <Size X="210.0000" Y="91.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="210.0000" Y="98.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="1.0000" Y="0.4000" />
                <PreSize X="1.0000" Y="0.3714" />
                <FileData Type="Normal" Path="Assets/Images/resources-2x/chopstick.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Assets/Images/resources-2x/roll.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>