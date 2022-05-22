import { ApiProperty } from '@nestjs/swagger';
import { ValidateIf } from 'class-validator';

export class NewContentMyPostDto {
  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  id: number;

  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  content: string;
}
