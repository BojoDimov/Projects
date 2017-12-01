import { AudioKrucPage } from './app.po';

describe('audio-kruc App', () => {
  let page: AudioKrucPage;

  beforeEach(() => {
    page = new AudioKrucPage();
  });

  it('should display welcome message', () => {
    page.navigateTo();
    expect(page.getParagraphText()).toEqual('Welcome to app!');
  });
});
